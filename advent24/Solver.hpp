#pragma once

#include <concepts>
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
#include <junelib/Timedelta.hpp>
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
        auto [result, duration] =
            june::ChronoTimer::time_function([this, input_type] {
                return get_solution_string(input_type);
            });

        std::println("{}", M::LABEL);
        std::println("Solution: {}", result);

        if (duration.to_ms() < 1.0) {
            std::println(
                "Time: {} ms ({} μs)", duration.to_ms(), duration.to_us()
            );
        }
        else if (duration.to_s() < 1.0) {
            std::println("Time: {} ms", duration.to_ms());
        }
        else {
            std::println("Time: {} s", duration.to_s());
        }
    }
};

} // namespace aoc
