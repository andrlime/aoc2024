#pragma once

#include <cmath>
#include <numeric>
#include <optional>
#include <string>
#include <utility>

#include <advent24/Config.hpp>
#include <advent24/day1/Shared.hpp>
#include <junelib/StringUtil.hpp>

namespace aoc::solutions::day1 {

struct Part1 {
    using t = NumberLists;

    static constexpr std::string NAME = "1a";
    static constexpr std::string LABEL = "Day 1, Part 1";

    static std::optional<std::string> get_input_path(InputType input_type) {
        switch (input_type) {
            case InputType::Small: return "day1/small.txt";
            case InputType::Large: return "day1/large.txt";
            case InputType::Testing: return std::nullopt;
        }
        std::unreachable();
    }

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
