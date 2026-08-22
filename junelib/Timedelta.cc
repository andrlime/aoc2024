#include <ratio>

#include <junelib/Timedelta.hpp>

namespace june {

Timedelta::Timedelta(std::chrono::nanoseconds ns) : ns_(ns) {}

Timedelta Timedelta::of_ns(std::chrono::nanoseconds ns) {
    return Timedelta{ns};
}

template <typename Ratio> double Timedelta::to() const {
    return std::chrono::duration<double, Ratio>(ns_).count();
}

double Timedelta::to_ns() const {
    return to<std::nano>();
}

double Timedelta::to_us() const {
    return to<std::micro>();
}

double Timedelta::to_ms() const {
    return to<std::milli>();
}

double Timedelta::to_s() const {
    return to<std::ratio<1>>();
}

double Timedelta::to_min() const {
    return to<std::ratio<60>>();
}

double Timedelta::to_hours() const {
    return to<std::chrono::hours::period>();
}

double Timedelta::to_days() const {
    return to<std::chrono::days::period>();
}

Timedelta Timedelta::operator+(const Timedelta& other) const {
    return Timedelta::of_ns(ns_ + other.ns_);
}

Timedelta Timedelta::operator-(const Timedelta& other) const {
    return Timedelta::of_ns(ns_ - other.ns_);
}

} // namespace june
