#include <cerrno>
#include <stdexcept>
#include <system_error>
#include <utility>

#include <junelib/SysUtil.hpp>
#include <unistd.h>

namespace june {

FdOpen::FdOpen(const std::string& path, int flags, mode_t mode) :
    fd_(::open(path.c_str(), flags, mode)) {
    if (fd_ < 0) {
        const std::error_code err(errno, std::generic_category());
        throw std::runtime_error(
            "FdOpen: failed to open '" + path + "': " + err.message()
        );
    }
}

FdOpen::~FdOpen() {
    if (fd_ >= 0) {
        ::close(fd_);
    }
}

FdOpen::FdOpen(FdOpen&& other) noexcept : fd_(std::exchange(other.fd_, -1)) {}

FdOpen& FdOpen::operator=(FdOpen&& other) noexcept {
    if (this != &other) {
        if (fd_ >= 0) {
            ::close(fd_);
        }
        fd_ = std::exchange(other.fd_, -1);
    }
    return *this;
}

} // namespace june
