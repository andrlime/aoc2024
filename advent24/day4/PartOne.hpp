#pragma once

#include <string>

#include <advent24/Config.hpp>
#include <advent24/day4/Shared.hpp>
#include <junelib/StringUtil.hpp>

namespace aoc::solutions::day4 {

struct Part1 {
    using t = LetterGraph;

    static constexpr std::string NAME = "4a";
    static constexpr std::string LABEL = "Day 4, Part 1";
    static constexpr InputListType INPUTS = {
        {"day4/small.txt", "day4/large.txt"}
    };

    static auto parse_input(const std::string& s) -> t {
        auto lines = june::strings::split(s, '\n');
        return LetterGraph{june::strings::remove_blank(lines)};
    }

    static auto solve(const t& graph) -> std::string {
        const int count = graph.dfs_wrapper();
        return std::to_string(count);
    }
};

} // namespace aoc::solutions::day4
