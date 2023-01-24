#include "day_03_rucksack_reorganization.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc_2022::day_3;


TEST(day_3_part_1, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_1(iss), 157);
}

TEST(day_3_part_2, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_2(iss), 70);
}

TEST(day_3_puzzle_main, output) {
    std::ostringstream oss{};
    puzzle_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Part 1: sum of priorities = 7795\n"
        "Part 2: sum of priorities = 2703\n"
    ));
}
