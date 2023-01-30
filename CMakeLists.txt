cmake_minimum_required(VERSION 3.22)

project("aoc_2022"
    VERSION 1.0
    DESCRIPTION "My solutions to the Advent of Code 2022 (C++)."
    HOMEPAGE_URL https://github.com/rturrado/aoc_2022.git
    LANGUAGES C CXX
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)

if(AOC_2022_BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(test)
endif()
