#pragma once

#include <numeric>
#include <optional>
#include <ranges>
#include <string>
#include <utility>

#include <advent24/Config.hpp>
#include <advent24/day1/Shared.hpp>
#include <junelib/StringUtil.hpp>

namespace aoc::solutions::day1 {

struct Part2 {
    using t = NumberFrequencies;

    static constexpr std::string NAME = "1b";
    static constexpr std::string LABEL = "Day 1, Part 2";

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
        return NumberFrequencies::from_lines(lines);
    }

    static auto solve(const t& numbers) -> std::string {
        auto left = numbers.get_left();
        auto right = numbers.get_right();

        const int soln = std::ranges::fold_left(
            left | std::views::all, 0, [&](int acc, std::pair<int, int> kv) {
                const int k = kv.first;
                const int v = kv.second;
                return acc += v * (k * right[k]);
            }
        );

        return std::to_string(soln);
    }
};

} // namespace aoc::solutions::day1
