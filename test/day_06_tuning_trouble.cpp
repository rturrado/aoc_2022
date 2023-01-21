#include "day_06_tuning_trouble.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc_2022::day_6;


TEST(day_6_part_1, puzzle_example_1) {
    std::istringstream iss{ puzzle_example_1_sv.data() };
    EXPECT_EQ(part_1(iss), 7);
}
TEST(day_6_part_1, puzzle_example_2) {
    std::istringstream iss{ puzzle_example_2_sv.data() };
    EXPECT_EQ(part_1(iss), 5);
}
TEST(day_6_part_1, puzzle_example_3) {
    std::istringstream iss{ puzzle_example_3_sv.data() };
    EXPECT_EQ(part_1(iss), 6);
}
TEST(day_6_part_1, puzzle_example_4) {
    std::istringstream iss{ puzzle_example_4_sv.data() };
    EXPECT_EQ(part_1(iss), 10);
}
TEST(day_6_part_1, puzzle_example_5) {
    std::istringstream iss{ puzzle_example_5_sv.data() };
    EXPECT_EQ(part_1(iss), 11);
}

TEST(day_6_part_2, puzzle_example_1) {
    std::istringstream iss{ puzzle_example_1_sv.data() };
    EXPECT_EQ(part_2(iss), 19);
}
TEST(day_6_part_2, puzzle_example_2) {
    std::istringstream iss{ puzzle_example_2_sv.data() };
    EXPECT_EQ(part_2(iss), 23);
}
TEST(day_6_part_2, puzzle_example_3) {
    std::istringstream iss{ puzzle_example_3_sv.data() };
    EXPECT_EQ(part_2(iss), 23);
}
TEST(day_6_part_2, puzzle_example_4) {
    std::istringstream iss{ puzzle_example_4_sv.data() };
    EXPECT_EQ(part_2(iss), 29);
}
TEST(day_6_part_2, puzzle_example_5) {
    std::istringstream iss{ puzzle_example_5_sv.data() };
    EXPECT_EQ(part_2(iss), 26);
}

TEST(day_6_main, output) {
    std::ostringstream oss{};
    main(oss);
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        "Part 1: start of packet marker = 1920\n"
        "Part 2: start of message marker = 2334\n"
    ));
}
