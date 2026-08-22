#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <print>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace aoc::solutions::day5 {

struct Ordering {
    std::vector<int> elements;
    std::unordered_set<int> set_of_elems;

    static Ordering of_string(const std::string& str, char delim = ',') {
        auto tokens = june::strings::split(str, delim);
        auto view = tokens | std::views::transform([](const std::string& s) {
                        return std::stoi(s);
                    });
        return {
            std::vector<int>(view.begin(), view.end()),
            std::unordered_set<int>(view.begin(), view.end()),
        };
    }
};

struct Edge {
    int from;
    int to;

    static Edge of_string(const std::string& str) {
        Ordering numbers = Ordering::of_string(str, '|');
        assert(numbers.elements.size() == 2);
        return {.from = numbers.elements.at(0), .to = numbers.elements.at(1)};
    }

    [[nodiscard]] bool is_valid(const Ordering& ordering) const {
        if (!ordering.set_of_elems.contains(from)) {
            return false;
        }
        if (!ordering.set_of_elems.contains(to)) {
            return false;
        }
        return true;
    }
};

struct State {
    std::vector<Edge> edges;
    std::vector<Ordering> orderings;

    static State of_string(const std::string& s) {
        auto lines = june::strings::split(s, '\n');

        std::vector<Edge> edges;
        std::vector<Ordering> orderings;

        bool reached_empty_line = false;
        for (const std::string& str : lines) {
            if (str.size() == 0) {
                reached_empty_line = true;
                continue;
            }

            if (reached_empty_line) {
                orderings.emplace_back(Ordering::of_string(str));
            }
            else {
                edges.emplace_back(Edge::of_string(str));
            }
        }

        return {.edges = edges, .orderings = orderings};
    }
};

class SequenceGraph {
    using TopologicalOrder = std::unordered_map<int, int>;

public:
    bool is_in_topological_order(const Ordering& input) const {
        const TopologicalOrder& order = get_topological_order(input);

        return std::ranges::is_sorted(input.elements, {}, [&](int x) {
            return order.at(x);
        });
    }

    Ordering topological_sort(const Ordering& input) const {
        const TopologicalOrder& order = get_topological_order(input);

        auto pairs_view = input.elements | std::views::transform([&](int x) {
                              return std::make_pair(x, order.at(x));
                          });

        std::vector<std::pair<int, int>> pairs(
            pairs_view.begin(), pairs_view.end()
        );
        std::ranges::sort(pairs, {}, &std::pair<int, int>::second);

        auto result_view =
            pairs | std::views::transform(&std::pair<int, int>::first);
        return {std::vector<int>(result_view.begin(), result_view.end())};
    }

    void add_edge(Edge edge) { all_edges.emplace_back(edge); }

private:
    TopologicalOrder get_topological_order(const Ordering& input) const {
        std::unordered_map<int, size_t> indegrees;
        std::unordered_map<int, std::unordered_set<int>> adj_list;

        for (const Edge& edge : all_edges) {
            if (!edge.is_valid(input)) {
                continue;
            }

            indegrees.try_emplace(edge.from, 0);
            auto [_, inserted] = adj_list[edge.from].insert(edge.to);
            if (inserted) {
                ++indegrees[edge.to];
            }
        }

        std::queue<int> next_to_process;
        for (const auto& [node, degree] : indegrees) {
            if (degree == 0) {
                next_to_process.push(node);
            }
        }

        std::vector<int> topo_order;
        while (!next_to_process.empty()) {
            const int next = next_to_process.front();
            next_to_process.pop();

            topo_order.emplace_back(next);
            for (int forward_edge : adj_list[next]) {
                if (--indegrees.at(forward_edge) == 0) {
                    next_to_process.push(forward_edge);
                }
            }
        }

        TopologicalOrder positions;
        for (size_t i = 0; i < topo_order.size(); ++i) {
            positions[topo_order[i]] = i;
        }

        return positions;
    }

    std::vector<Edge> all_edges;
};

} // namespace aoc::solutions::day5
