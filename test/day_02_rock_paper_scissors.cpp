#include "day_02_rock_paper_scissors.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <sstream>  // istringstream

using namespace aoc_2022::day_2;


TEST(day_2_part_1, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_1(iss), 15);
}

TEST(day_2_part_2, puzzle_example) {
std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_2(iss), 12);
}

TEST(day_2_main, output) {
    std::ostringstream oss{};
    main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Part 1: total score = 15632\n"
        "Part 2: total score = 14416\n"
    ));
}
