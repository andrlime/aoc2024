file(GLOB junelib_SOURCES "junelib/*.cc")

add_library(junelib STATIC ${junelib_SOURCES})
target_include_directories(junelib PUBLIC ${CMAKE_SOURCE_DIR})
target_compile_features(junelib PUBLIC cxx_std_${CMAKE_CXX_STANDARD})

file(GLOB_RECURSE aoc_SOURCES "advent24/*.cc")

add_executable(aoc ${aoc_SOURCES})
set_property(TARGET aoc PROPERTY OUTPUT_NAME aoc2024)
target_compile_features(aoc PRIVATE cxx_std_${CMAKE_CXX_STANDARD})
target_include_directories(aoc PRIVATE ${CMAKE_SOURCE_DIR})
target_link_libraries(aoc PRIVATE junelib)
