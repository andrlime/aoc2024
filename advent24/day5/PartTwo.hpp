#pragma once

#include <string>

#include <advent24/Config.hpp>
#include <advent24/day5/Shared.hpp>
#include <junelib/StringUtil.hpp>

namespace aoc::solutions::day5 {

struct Part2 {
    using t = State;

    static constexpr std::string NAME = "5b";
    static constexpr std::string LABEL = "Day 5, Part 2";
    static constexpr InputListType INPUTS = {
        {"day5/small.txt", "day5/large.txt"}
    };

    static auto parse_input(const std::string& s) -> t {
        return State::of_string(s);
    }

    static auto solve(const t& t) -> std::string {
        SequenceGraph graph;
        auto add_edge_callable = std::bind_front(
            std::mem_fn(&SequenceGraph::add_edge), std::ref(graph)
        );
        std::ranges::for_each(t.edges, add_edge_callable);

        const int total = std::ranges::fold_left(
            t.orderings, 0, [&](int acc, const Ordering& ordering) {
                if (graph.is_in_topological_order(ordering)) {
                    return acc;
                }

                Ordering correct_ordering = graph.topological_sort(ordering);
                const size_t middle_index =
                    correct_ordering.elements.size() / 2;
                return acc + correct_ordering.elements[middle_index];
            }
        );

        return std::to_string(total);
    }
};

} // namespace aoc::solutions::day5
