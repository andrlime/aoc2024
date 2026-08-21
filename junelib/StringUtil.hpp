#pragma once

#include <span>
#include <string>
#include <vector>

namespace june::strings {

std::vector<std::string> split(const std::string& string, char delimiter);

std::string strip(std::string string);

std::vector<std::string> remove_blank(std::span<const std::string> strings);

} // namespace june::strings
