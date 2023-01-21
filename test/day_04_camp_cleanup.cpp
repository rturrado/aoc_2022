#include "day_04_camp_cleanup.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc_2022::day_4;


TEST(day_4_part_1, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_1(iss), 2);
}

TEST(day_4_part_2, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_2(iss), 4);
}

TEST(day_4_main, output) {
    std::ostringstream oss{};
    main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Part 1: number of fully contained ranges = 431\n"
        "Part 2: number of partially contained ranges = 823\n"
    ));
}
