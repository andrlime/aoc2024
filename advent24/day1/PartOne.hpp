#pragma once

#include <cmath>
#include <numeric>
#include <string>

#include <advent24/Config.hpp>
#include <advent24/day1/Shared.hpp>
#include <junelib/StringUtil.hpp>

namespace aoc::solutions::day1 {

struct Part1 {
    using t = NumberLists;

    static constexpr std::string NAME = "1a";
    static constexpr std::string LABEL = "Day 1, Part 1";
    static constexpr InputListType INPUTS = {
        {"day1/small.txt", "day1/large.txt"}
    };

    static auto parse_input(const std::string& s) -> t {
        auto lines = june::strings::split(s, '\n');
        return NumberLists::from_lines(lines);
    }

    static auto solve(const t& numbers) -> std::string {
        const int soln = std::ranges::fold_left(
            numbers.get_zipped(), 0, [](int acc, std::pair<int, int> nums) {
                return acc + std::abs(nums.first - nums.second);
            }
        );

        return std::to_string(soln);
    }
};

} // namespace aoc::solutions::day1
