#pragma once

#include <algorithm>
#include <ranges>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace aoc::solutions::day1 {

struct TwoNumbers {
    using t = std::pair<int, int>;

    static t t_of_string(const std::string& s) {
        int left = 0;
        int right = 0;
        int buffer = 0;
        for (const char c : s) {
            if (c == ' ') {
                if (buffer > 0) {
                    left = buffer;
                    buffer = 0;
                }
                continue;
            }
            buffer *= 10;
            buffer += (c - '0');
        }
        right = buffer;
        return std::make_pair(left, right);
    }
};

class NumberLists {
public:
    void add_left(int x) { left_.push_back(x); }

    void add_right(int x) { right_.push_back(x); }

    void sort() {
        std::ranges::sort(left_, std::ranges::greater());
        std::ranges::sort(right_, std::ranges::greater());
    }

    auto get_zipped() const { return std::views::zip(left_, right_); }

    static NumberLists from_lines(const std::vector<std::string>& lines) {
        NumberLists n;
        for (const std::string& s : lines) {
            auto numbers = TwoNumbers::t_of_string(s);
            n.add_left(numbers.first);
            n.add_right(numbers.second);
        }
        n.sort();
        return n;
    }

private:
    std::vector<int> left_;
    std::vector<int> right_;
};

class NumberFrequencies {
    using FrequencyMap = std::unordered_map<int, int>;

public:
    void add_left(int x) { left_[x]++; }

    void add_right(int x) { right_[x]++; }

    FrequencyMap get_left() const { return left_; }

    FrequencyMap get_right() const { return right_; }

    static NumberFrequencies from_lines(const std::vector<std::string>& lines) {
        NumberFrequencies n;
        for (const std::string& s : lines) {
            auto numbers = TwoNumbers::t_of_string(s);
            n.add_left(numbers.first);
            n.add_right(numbers.second);
        }
        return n;
    }

private:
    FrequencyMap left_;
    FrequencyMap right_;
};

} // namespace aoc::solutions::day1
