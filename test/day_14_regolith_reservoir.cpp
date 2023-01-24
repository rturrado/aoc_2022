#include "day_14_regolith_reservoir.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc_2022::day_14;


TEST(day_14_part_1, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_1(iss), 24);
}

TEST(day_14_part_2, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_2(iss), 93);
}

TEST(day_14_puzzle_main, output) {
    std::ostringstream oss{};
    puzzle_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Part 1: units of sand = 719\n"
        "Part 2: units of sand = 23390\n"
    ));
}
