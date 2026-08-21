#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace aoc::solutions::day4 {

enum class Letter : uint8_t { Invalid, X, M, A, S };

class LetterGraph {
    using Grid = std::vector<Letter>;

public:
    explicit LetterGraph(const std::vector<std::string>& lines) {
        const int rows = static_cast<int>(lines.size());
        const int cols = static_cast<int>(lines[0].length());
        rows_ = rows;
        cols_ = cols;
        grid_.resize(
            static_cast<size_t>(rows) * static_cast<size_t>(cols),
            Letter::Invalid
        );

        for (int row = 0; row < rows; row++) {
            const std::string& l = lines[row];
            for (int col = 0; col < cols; col++) {
                set_(row, col, letter_of_char(l[col]));
            }
        }
    }

    int convolution_wrapper() const {
        int total_count = 0;
        // row, col tracks top left corner
        for (int row = 0; row < rows_ - 2; row++) {
            for (int col = 0; col < cols_ - 2; col++) {
                if (!is_valid_region_(row, col)) {
                    continue;
                }
                total_count++;
            }
        }
        return total_count;
    }

    int dfs_wrapper() const {
        int total_count = 0;
        for (int row = 0; row < rows_; row++) {
            for (int col = 0; col < cols_; col++) {
                const auto letter = at_(row, col);
                if (!letter || *letter != Letter::X) {
                    continue;
                }
                for (const auto dpos : NEIGHBORS) {
                    dfs_(row, col, total_count, 'X', dpos);
                }
            }
        }
        return total_count;
    }

private:
    bool is_valid_region_(int row, int col) const {
        const auto center = at_(row + 1, col + 1);
        if (!center || *center != Letter::A) {
            return false;
        }

        const auto topleft = at_(row, col);
        const auto topright = at_(row, col + 2);
        const auto bottomleft = at_(row + 2, col);
        const auto bottomright = at_(row + 2, col + 2);
        if (!topleft || !topright || !bottomleft || !bottomright) {
            return false;
        }

        bool horizontal = true;
        horizontal &= *topleft == *topright;
        horizontal &= (*topleft == Letter::M || *topleft == Letter::S);
        horizontal &= *bottomleft == *bottomright;
        horizontal &= (*bottomleft == Letter::M || *bottomleft == Letter::S);
        horizontal &= *topleft != *bottomleft;
        if (horizontal) {
            return true;
        }

        bool vertical = true;
        vertical &= *topleft == *bottomleft;
        vertical &= (*topleft == Letter::M || *topleft == Letter::S);
        vertical &= *topright == *bottomright;
        vertical &= (*topright == Letter::M || *topright == Letter::S);
        vertical &= *topleft != *topright;

        return vertical;
    }

    void dfs_(
        int row, int col, int& total, char cur_char,
        const std::pair<int, int>& delta
    ) const {
        if (cur_char == 'S') {
            total++;
            return;
        }

        const int dx = delta.first;
        const int dy = delta.second;
        auto letter = at_(row + dx, col + dy);
        if (!letter) {
            return;
        }
        const char next = next_char_of_char(cur_char);
        if (char_of_letter(*letter) != next) {
            return;
        }
        dfs_(row + dx, col + dy, total, next, delta);
    }

    static char next_char_of_char(char c) {
        switch (c) {
            case 'X': return 'M';
            case 'M': return 'A';
            case 'A': return 'S';
            case 'S': return '_';
            default:
                throw std::runtime_error(std::string("Invalid character ") + c);
        }
    }

    static Letter letter_of_char(char c) {
        switch (c) {
            case 'X': return Letter::X;
            case 'M': return Letter::M;
            case 'A': return Letter::A;
            case 'S': return Letter::S;
            default:
                throw std::runtime_error(std::string("Invalid character ") + c);
        }
    }

    static char char_of_letter(Letter l) {
        switch (l) {
            case Letter::X: return 'X';
            case Letter::M: return 'M';
            case Letter::A: return 'A';
            case Letter::S: return 'S';
            default: throw std::runtime_error("Invalid letter");
        }
    }

    std::optional<Letter> at_(int row, int col) const {
        if (row < 0 || row >= rows_) {
            return std::nullopt;
        }
        if (col < 0 || col >= cols_) {
            return std::nullopt;
        }
        return grid_
            [(static_cast<size_t>(row) * cols_) + static_cast<size_t>(col)];
    }

    void set_(int row, int col, Letter letter) {
        grid_[(static_cast<size_t>(row) * cols_) + static_cast<size_t>(col)] =
            letter;
    }

    int rows_;
    int cols_;
    Grid grid_;

    static constexpr std::array<std::pair<int, int>, 8> NEIGHBORS = {
        {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}
    };
};

} // namespace aoc::solutions::day4
