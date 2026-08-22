#include <advent24/day1/PartOne.hpp>
#include <advent24/day1/PartTwo.hpp>
#include <advent24/day2/PartOne.hpp>
#include <advent24/day2/PartTwo.hpp>
#include <advent24/day3/PartOne.hpp>
#include <advent24/day3/PartTwo.hpp>
#include <advent24/day4/PartOne.hpp>
#include <advent24/day4/PartTwo.hpp>
#include <advent24/day5/PartOne.hpp>
#include <advent24/day5/PartTwo.hpp>
#include <advent24/example/ExampleSolution.hpp>
#include <advent24/Solver.hpp>

namespace aoc {

namespace {

template <Solution M> std::unique_ptr<SolverInterface>
try_solver(const Config& cfg) {
    if (cfg.solution_id != M::NAME) {
        return nullptr;
    }
    return std::make_unique<Solver<M>>();
}

template <Solution... Ms> std::unique_ptr<SolverInterface>
get_solver(const Config& cfg) {
    std::unique_ptr<SolverInterface> result;
    ((result = result ? std::move(result) : try_solver<Ms>(cfg)), ...);
    return result;
}

} // namespace

std::unique_ptr<SolverInterface> SolverInterface::of_cfg(const Config& cfg) {
    using namespace solutions;
    auto solver = get_solver<
        Example, day1::Part1, day1::Part2, day2::Part1, day2::Part2,
        day3::Part1, day3::Part2, day4::Part1, day4::Part2, day5::Part1,
        day5::Part2>(cfg);
    if (!solver) {
        throw std::runtime_error(
            std::format("no solution matching id '{}'", cfg.solution_id)
        );
    }
    return solver;
}

} // namespace aoc
