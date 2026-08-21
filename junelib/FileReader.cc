#include <cerrno>
#include <span>
#include <stdexcept>
#include <system_error>

#include <junelib/FileReader.hpp>
#include <junelib/SysUtil.hpp>
#include <sys/stat.h>
#include <unistd.h>

namespace june {

std::string FileReader::read(const std::string& path) {
    const FdOpen file(path);

    struct stat st{};
    if (::fstat(file.fd(), &st) != 0) {
        const std::error_code err(errno, std::generic_category());
        throw std::runtime_error(
            "FileReader: fstat failed for '" + path + "': " + err.message()
        );
    }

    std::string contents(static_cast<size_t>(st.st_size), '\0');
    const std::span<char> buffer(contents.data(), contents.size());

    size_t total_read = 0;
    while (total_read < contents.size()) {
        const std::span<char> remaining = buffer.subspan(total_read);
        const ssize_t n = ::read(file.fd(), remaining.data(), remaining.size());

        if (n < 0) {
            if (errno == EINTR) {
                continue;
            }

            const std::error_code err(errno, std::generic_category());
            throw std::runtime_error(
                "FileReader: read failed for '" + path + "': " + err.message()
            );
        }

        if (n == 0) {
            break; // file shrank concurrently
        }

        total_read += static_cast<size_t>(n);
    }

    contents.resize(total_read);
    return contents;
}

} // namespace june
