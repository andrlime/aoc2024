#pragma once

#include <numeric>
#include <optional>
#include <string>
#include <utility>

#include <advent24/Config.hpp>
#include <advent24/day3/Shared.hpp>

namespace aoc::solutions::day3 {

struct Part2 {
    using t = InstructionsList;

    static constexpr std::string NAME = "3b";
    static constexpr std::string LABEL = "Day 3, Part 2";

    static std::optional<std::string> get_input_path(InputType input_type) {
        switch (input_type) {
            case InputType::Small: return "day3/small_part2.txt";
            case InputType::Large: return "day3/large.txt";
            case InputType::Testing: return std::nullopt;
        }
        std::unreachable();
    }

    static auto parse_input(const std::string& s) -> t {
        Parser p{s};
        p.parse(ParserType::CheckDoDont);
        return p.get_instructions();
    }

    static auto solve(const t& instructions) -> std::string {
        const int sum = std::ranges::fold_left(
            instructions, 0,
            [](int acc, const MultiplicationInstruction& instruction) {
                return acc + instruction.interp();
            }
        );
        return std::to_string(sum);
    }
};

} // namespace aoc::solutions::day3
