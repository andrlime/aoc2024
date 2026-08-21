#pragma once

#include <cstdint>
#include <string_view>

namespace aoc {

enum class InputType : uint8_t { Small, Large, Testing };

InputType input_type_of_string(std::string_view input);
std::string_view string_of_input_type(InputType type);

struct Config {
    std::string_view solution_id;
    InputType input_type;

    static Config of_cli(int argc, char** argv);
};

} // namespace aoc
