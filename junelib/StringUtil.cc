#include <functional>
#include <ranges>
#include <sstream>

#include <junelib/StringUtil.hpp>

namespace june::strings {

std::vector<std::string> split(const std::string& string, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream ss(string);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.emplace_back(token);
    }

    return tokens;
}

std::string strip(std::string string) {
    string.erase(0, string.find_first_not_of(" \t\n\r\f\v"));
    string.erase(string.find_last_not_of(" \t\n\r\f\v") + 1);
    return string;
}

std::vector<std::string> remove_blank(std::span<const std::string> strings) {
    const auto predicate = std::not_fn(&std::string::empty);
    using NonBlankView = std::ranges::filter_view<
        std::span<const std::string>, decltype(predicate)>;

    NonBlankView view(strings, predicate);
    return {view.begin(), view.end()};
}

} // namespace june::strings
