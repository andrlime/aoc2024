#pragma once

#include <string>

namespace june {

struct FileReader {
    FileReader() = delete;

    static std::string read(const std::string& path);
};

} // namespace june
