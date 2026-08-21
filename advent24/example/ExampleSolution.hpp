#pragma once

#include <optional>
#include <string>
#include <utility>

#include <advent24/Config.hpp>

namespace aoc::solutions {

struct Example {
    using t = std::string;

    static constexpr std::string NAME = "example";
    static constexpr std::string LABEL = "Example";

    static std::optional<std::string> get_input_path(InputType input_type) {
        switch (input_type) {
            case InputType::Small: return "example/helloworld_small.txt";
            case InputType::Large: return "example/helloworld_large.txt";
            case InputType::Testing: return std::nullopt;
        }
        std::unreachable();
    }

    static auto parse_input(const std::string& s) -> t { return s; }

    static auto solve(const t& data) -> std::string { return data; }
};

} // namespace aoc::solutions
