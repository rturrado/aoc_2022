#include "day_07_no_space_left_on_device.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc_2022::day_7;


TEST(day_7_part_1, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_1(iss), 95437);
}

TEST(day_7_part_2, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_2(iss), 24933642);
}

TEST(day_7_puzzle_main, output) {
    std::ostringstream oss{};
    puzzle_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Part 1: total sizes = 1491614\n"
        "Part 2: size of smallest directory to free = 6400111\n"
    ));
}
