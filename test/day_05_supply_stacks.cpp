#include "day_05_supply_stacks.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc_2022::day_5;


TEST(day_5_part_1, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_1(iss, puzzle_example_queues), "CMZ");
}

TEST(day_5_part_2, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_2(iss, puzzle_example_queues), "MCD");
}

TEST(day_5_puzzle_main, output) {
    std::ostringstream oss{};
    puzzle_main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Part 1: message = QNNTGTPFN\n"
        "Part 2: message = GGNPJBTTR\n"
    ));
}
