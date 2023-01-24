#include "day_11_monkey_in_the_middle.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc_2022::day_11;


TEST(day_11_part_1, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_1(iss), 10605);
}

TEST(day_11_puzzle_main, output) {
    std::ostringstream oss{};
    puzzle_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Part 1: monkey business level = 120056\n"
    ));
}
