#pragma once

#include <concepts>
#include <cstdint>
#include <filesystem>
#include <format>
#include <memory>
#include <optional>
#include <print>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

#include <advent24/Config.hpp>
#include <junelib/FileReader.hpp>
#include <junelib/MemoryUtil.hpp>
#include <junelib/StringUtil.hpp>
#include <junelib/Timing.hpp>

namespace aoc {

template <typename S>
concept Solution = requires(const std::string& input, typename S::t value) {
    typename S::t;

    { S::NAME } -> std::convertible_to<std::string>;
    { S::LABEL } -> std::convertible_to<std::string>;
    { S::INPUTS } -> std::convertible_to<InputListType>;

    { S::parse_input(input) } -> std::same_as<typename S::t>;
    { S::solve(value) } -> std::convertible_to<std::string>;
};

struct SolverInterface : june::Noncopyable {
    virtual ~SolverInterface() = default;

    static std::unique_ptr<SolverInterface> of_cfg(const Config& cfg);

    virtual std::string get_solution_string(InputType input_type) = 0;
    virtual void time_and_solve(InputType input_type) = 0;
};

template <Solution M> struct Solver final : public SolverInterface {
    std::string get_solution_string(InputType input_type) override {
        const std::optional<std::string_view>& path =
            M::INPUTS.at(std::to_underlying(input_type));
        if (!path) {
            throw std::runtime_error(
                std::format(
                    "invalid input: {}/{}", M::NAME,
                    string_of_input_type(input_type)
                )
            );
        }

        std::filesystem::path input_directory("./inputs");
        const std::string input =
            june::FileReader::read(input_directory / *path);

        const typename M::t parsed = M::parse_input(input);
        return june::strings::strip(M::solve(parsed));
    }

    void time_and_solve(InputType input_type) override {
        static constexpr uint64_t US_PER_MS = 1000;

        auto [result, duration_ms] =
            june::ChronoTimer::time_function([this, input_type] {
                return get_solution_string(input_type);
            });

        std::println("{}", M::LABEL);
        std::println("Solution: {}", result);

        if (duration_ms < 1.0) {
            std::println(
                "Time: {} ms ({} μs)", duration_ms, duration_ms * US_PER_MS
            );
        }
        else {
            std::println("Time: {} ms", duration_ms);
        }
    }
};

} // namespace aoc
