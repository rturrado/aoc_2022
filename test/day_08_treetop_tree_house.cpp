#include "day_08_treetop_tree_house.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc_2022::day_8;


TEST(day_8_part_1, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    forest_t rows{};
    forest_t cols{};
    read_forest_rows_and_cols(iss, rows, cols);
    EXPECT_EQ(part_1(rows, cols), 21);
}

TEST(day_8_part_2, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    forest_t rows{};
    forest_t cols{};
    read_forest_rows_and_cols(iss, rows, cols);
    EXPECT_EQ(part_2(rows, cols), 8);
}

TEST(day_8_puzzle_main, output) {
    std::ostringstream oss{};
    puzzle_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Part 1: number of visible trees = 1776\n"
        "Part 2: highest scenic score = 234416\n"
    ));
}
