cmake_minimum_required(VERSION 3.20)

project(
	aoc
	VERSION 1.0
	DESCRIPTION "Advent of Code 2024 in C++"
	LANGUAGES CXX
)

include("cmake/build-type.cmake")

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
endif()

if(APPLE)
	include("cmake/macos-hotfix.cmake")
endif()

include("cmake/init-project.cmake")
