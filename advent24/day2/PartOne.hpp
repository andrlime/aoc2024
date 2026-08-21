#pragma once

#include <numeric>
#include <optional>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

#include <advent24/Config.hpp>
#include <advent24/day2/Shared.hpp>
#include <junelib/StringUtil.hpp>

namespace aoc::solutions::day2 {

struct Part1 {
    using t = std::vector<NumberSequence::t>;

    static constexpr std::string NAME = "2a";
    static constexpr std::string LABEL = "Day 2, Part 1";

    static std::optional<std::string> get_input_path(InputType input_type) {
        switch (input_type) {
            case InputType::Small: return "day2/small.txt";
            case InputType::Large: return "day2/large.txt";
            case InputType::Testing: return std::nullopt;
        }
        std::unreachable();
    }

    static auto parse_input(const std::string& s) -> t {
        return june::strings::split(s, '\n')
               | std::views::transform(NumberSequence::t_of_string)
               | std::ranges::to<std::vector>();
    }

    static auto solve(const t& data) -> std::string {
        const int count = std::ranges::fold_left(
            data, 0, [](int acc, const NumberSequence::t& seq) {
                const bool valid =
                    NumberSequence::is_valid_simple_sequence(seq);
                return acc + static_cast<int>(valid);
            }
        );

        return std::to_string(count);
    }
};

} // namespace aoc::solutions::day2
