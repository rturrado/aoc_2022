#include "day_09_rope_bridge.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc_2022::day_9;


TEST(day_9_part_1, puzzle_example_1) {
    std::istringstream iss{ puzzle_example_1_sv.data() };
    EXPECT_EQ(part_1(iss), 13);
}

TEST(day_9_part_2, puzzle_example_1) {
    std::istringstream iss{ puzzle_example_1_sv.data() };
    EXPECT_EQ(part_2(iss), 1);
}

TEST(day_9_part_2, puzzle_example_2) {
    std::istringstream iss{ puzzle_example_2_sv.data() };
    EXPECT_EQ(part_2(iss), 36);
}

TEST(day_9_puzzle_main, output) {
    std::ostringstream oss{};
    puzzle_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Part 1: number of visited positions = 6243\n"
        "Part 2: number of visited positions = 2630\n"
    ));
}
