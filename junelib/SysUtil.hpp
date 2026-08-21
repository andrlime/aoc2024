#pragma once

#include <string>

#include <fcntl.h>
#include <junelib/MemoryUtil.hpp>
#include <sys/types.h>

namespace june {

struct FdOpen : Noncopyable {
    explicit FdOpen(
        const std::string& path, int flags = O_RDONLY, mode_t mode = 0
    );
    ~FdOpen();

    FdOpen(FdOpen&& other) noexcept;
    FdOpen& operator=(FdOpen&& other) noexcept;

    [[nodiscard]] int fd() const noexcept { return fd_; }

private:
    int fd_;
};

} // namespace june
