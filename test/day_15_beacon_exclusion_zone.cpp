#include "day_15_beacon_exclusion_zone.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc_2022::day_15;


TEST(day_15_part_1, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_1(iss, 10), 26);
}

TEST(day_15_part_2, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_2(iss, 20), 56000011);
}

TEST(day_15_puzzle_main, output) {
    std::ostringstream oss{};
    puzzle_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Part 1: number of positions that cannot contain a beacon in row 2'000'000 = 6425133\n"
        "Part 2: tuning frequency = 10996191429555\n"
    ));
}
