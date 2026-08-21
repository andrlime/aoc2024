#include <exception>
#include <print>

#include <advent24/Config.hpp>
#include <advent24/Solver.hpp>

int main(int argc, char** argv) try {
    const auto cfg = aoc::Config::of_cli(argc, argv);
    aoc::SolverInterface::of_cfg(cfg)->time_and_solve(cfg.input_type);

    return 0;
} catch (const std::exception& e) {
    std::println(stderr, "aoc: {}", e.what());
    return 1;
} catch (...) {
    std::println(stderr, "aoc: unhandled error");
    return 1;
}
