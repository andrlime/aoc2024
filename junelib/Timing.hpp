#pragma once

#include <chrono>
#include <concepts>
#include <type_traits>
#include <utility>

#include <junelib/Timedelta.hpp>

namespace june {

template <typename T> struct TimingResult {
    T value;
    Timedelta duration;
};

struct ChronoTimer {
    ChronoTimer() = delete;

    template <typename F> requires std::invocable<F>
    static auto time_function(F&& f) {
        using Result = std::invoke_result_t<F>;

        auto start = std::chrono::high_resolution_clock::now();
        Result value = std::forward<F>(f)();
        auto end = std::chrono::high_resolution_clock::now();

        Timedelta duration = Timedelta::of_ns(
            std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
        );
        return TimingResult<Result>{std::move(value), duration};
    }
};

} // namespace june
