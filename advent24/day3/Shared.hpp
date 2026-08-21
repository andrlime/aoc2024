#pragma once

#include <cstddef>
#include <cstdint>
#include <stack>
#include <string>
#include <vector>

namespace aoc::solutions::day3 {

enum class ParserType : uint8_t { Default, CheckDoDont };

class MultiplicationInstruction {
public:
    MultiplicationInstruction(int l, int r) : left_(l), right_(r) {}

    int interp() const { return left_ * right_; }

private:
    int left_;
    int right_;
};

using InstructionsList = std::vector<MultiplicationInstruction>;

class Parser {
public:
    explicit Parser(const std::string& s) : program_(s), len_(s.length()) {}

    void parse(ParserType t) {
        while (pc_ < len_) {
            const char opcode = program_[pc_];
            switch (opcode) {
                case 'm':
                    if (is_enabled_) {
                        parse_mult_();
                    }
                case 'd':
                    if (t == ParserType::CheckDoDont) {
                        parse_do_dont_();
                    }
                default: break;
            }

            advance_();
        }
    }

    InstructionsList get_instructions() const { return instructions_; }

private:
    void parse_do_dont_() {
        if (program_[pc_] != 'd') {
            return;
        }

        advance_();
        if (program_[pc_] != 'o') {
            return;
        }

        advance_();
        if (program_[pc_] == '(') {
            advance_();
            if (program_[pc_] == ')') {
                is_enabled_ = true;
            }
            return;
        }
        if (program_[pc_] != 'n') {
            return;
        }

        advance_();
        if (program_[pc_] != '\'') {
            return;
        }

        advance_();
        if (program_[pc_] != 't') {
            return;
        }

        advance_();
        if (program_[pc_] == '(') {
            advance_();
            if (program_[pc_] == ')') {
                is_enabled_ = false;
            }
            return;
        }
    }

    void parse_mult_() {
        if (program_[pc_] != 'm') {
            return;
        }

        advance_();
        if (program_[pc_] != 'u') {
            return;
        }

        advance_();
        if (program_[pc_] != 'l') {
            return;
        }

        advance_();
        if (program_[pc_] != '(') {
            return;
        }

        advance_();
        int current_value = 0;
        while (program_[pc_] != ')') {
            const char c = program_[pc_];
            if (!is_valid_character(c)) {
                stack_ = std::stack<int>();
                return;
            }
            if (c == ',' && current_value > 0) {
                stack_.push(current_value);
                current_value = 0;
            }
            if (is_digit(c)) {
                current_value *= 10;
                current_value += (c - '0');
            }
            advance_();
        }
        stack_.push(current_value);

        if (stack_.size() > 2) {
            return;
        }

        const int right = stack_.top();
        stack_.pop();

        const int left = stack_.top();
        stack_.pop();

        instructions_.emplace_back(left, right);
    }

    static bool is_digit(char c) { return c >= '0' && c <= '9'; }

    static bool is_valid_character(char c) {
        if (is_digit(c)) {
            return true;
        }
        return c == ',';
    }

    void advance_() { pc_++; }

    InstructionsList instructions_;
    std::stack<int> stack_;
    std::string program_;
    bool is_enabled_{true};
    size_t pc_{0};
    size_t len_;
};

} // namespace aoc::solutions::day3
