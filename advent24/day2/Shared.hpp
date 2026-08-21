#pragma once

#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace aoc::solutions::day2 {

enum class SequenceType : uint8_t {
    Uninitialised,
    Increasing,
    Decreasing
};

struct NumberSequence {
    using t = std::vector<int>;

    static t t_of_string(const std::string& s) {
        std::vector<int> values;
        int buffer = 0;
        bool has_value = false;
        for (const char c : s) {
            if (c == ' ') {
                if (has_value) {
                    values.push_back(buffer);
                    buffer = 0;
                    has_value = false;
                }
                continue;
            }
            buffer *= 10;
            buffer += (c - '0');
            has_value = true;
        }
        values.push_back(buffer);
        return values;
    }

    static bool signs_ok(int d, SequenceType type) {
        switch (type) {
            case SequenceType::Increasing: return d >= 0;
            case SequenceType::Decreasing: return d <= 0;
            default: throw std::runtime_error("Invalid sign?");
        }
    }

    static bool is_valid_simple_sequence(const t& t) {
        auto type = SequenceType::Uninitialised;
        for (size_t i1 = 1; i1 < t.size(); i1++) {
            const int x0 = t[i1 - 1];
            const int x1 = t[i1];

            const int delta = x1 - x0;
            if (type == SequenceType::Uninitialised) {
                type = delta > 0 ? SequenceType::Increasing
                                 : SequenceType::Decreasing;
            }
            else if (!signs_ok(delta, type)) {
                return false;
            }
            if (std::abs(delta) > 3 || std::abs(delta) < 1) {
                return false;
            }
        }
        return true;
    }

    static bool is_valid_removeable_sequence(const t& t) {
        for (size_t skip = 0; skip < t.size(); skip++) {
            std::vector<int> container;
            for (size_t i0 = 0; i0 < t.size(); i0++) {
                if (i0 == skip) {
                    continue;
                }
                container.push_back(t[i0]);
            }
            if (is_valid_simple_sequence(container)) {
                return true;
            }
        }
        return false;
    }
};

} // namespace aoc::solutions::day2
