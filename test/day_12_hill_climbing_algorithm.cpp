#include "day_12_hill_climbing_algorithm.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc_2022::day_12;


TEST(day_12_part_1, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_1(iss), 31);
}

TEST(day_12_part_2, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_2(iss), 29);
}

TEST(day_12_main, output) {
    std::ostringstream oss{};
    main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Part 1: fewest steps = 456\n"
        "Part 2: fewest steps = 454\n"
    ));
}
