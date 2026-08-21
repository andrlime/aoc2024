#include <format>
#include <stdexcept>
#include <utility>

#include <advent24/Config.hpp>

namespace aoc {

InputType input_type_of_string(std::string_view input) {
    if (input == "small") {
        return InputType::Small;
    }
    if (input == "large") {
        return InputType::Large;
    }
    if (input == "testing") {
        return InputType::Testing;
    }
    throw std::runtime_error(std::format("invalid input type: {}", input));
}

std::string_view string_of_input_type(InputType type) {
    switch (type) {
        case InputType::Small: return "small";
        case InputType::Large: return "large";
        case InputType::Testing: return "testing";
    }
    std::unreachable();
}

Config Config::of_cli(int argc, char** argv) {
    if (argc < 2 || argc > 3) {
        throw std::runtime_error(
            std::format("invalid cli argument count {}", argc)
        );
    }

    std::string_view input = argc == 3 ? argv[2] : "large";
    return {.solution_id = argv[1], .input_type = input_type_of_string(input)};
}

} // namespace aoc
