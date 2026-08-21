file(GLOB_RECURSE aoc_SOURCES "src/*.cc")

add_executable(aoc ${aoc_SOURCES})
set_property(TARGET aoc PROPERTY OUTPUT_NAME aoc2024)
target_compile_features(aoc PRIVATE cxx_std_${CMAKE_CXX_STANDARD})
