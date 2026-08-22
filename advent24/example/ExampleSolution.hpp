#pragma once

#include <string>

#include <advent24/Config.hpp>

namespace aoc::solutions {

struct Example {
    using t = std::string;

    static constexpr std::string NAME = "example";
    static constexpr std::string LABEL = "Example";
    static constexpr InputListType INPUTS = {
        {"example/helloworld_small.txt", "example/helloworld_large.txt"}
    };

    static auto parse_input(const std::string& s) -> t { return s; }

    static auto solve(const t& data) -> std::string { return data; }
};

} // namespace aoc::solutions
