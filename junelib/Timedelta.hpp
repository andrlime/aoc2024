#pragma once

#include <chrono>

namespace june {

class Timedelta {
public:
    static Timedelta of_ns(std::chrono::nanoseconds ns);

    double to_ns() const;
    double to_us() const;
    double to_ms() const;
    double to_s() const;
    double to_min() const;
    double to_hours() const;
    double to_days() const;

    Timedelta operator+(const Timedelta& other) const;
    Timedelta operator-(const Timedelta& other) const;

private:
    explicit Timedelta(std::chrono::nanoseconds ns);

    template <typename Ratio> double to() const;

    std::chrono::nanoseconds ns_;
};

} // namespace june
