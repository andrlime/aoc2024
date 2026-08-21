#pragma once

#include <chrono>
#include <concepts>
#include <ratio>
#include <type_traits>
#include <utility>

namespace june {

template <typename T> struct TimingResult {
    T value;
    double duration;
};

struct ChronoTimer {
    ChronoTimer() = delete;

    template <typename Units = std::milli, typename F>
    requires std::invocable<F>
             && std::same_as<Units, std::ratio<Units::num, Units::den>>
    static auto time_function(F&& f) {
        using Result = std::invoke_result_t<F>;

        auto start = std::chrono::high_resolution_clock::now();
        Result value = std::forward<F>(f)();
        auto end = std::chrono::high_resolution_clock::now();

        double duration =
            std::chrono::duration<double, Units>(end - start).count();
        return TimingResult<Result>{std::move(value), duration};
    }
};

} // namespace june
