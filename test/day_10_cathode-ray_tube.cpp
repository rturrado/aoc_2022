#include "day_10_cathode-ray_tube.hpp"

#include <fmt/format.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <string_view>

using namespace aoc_2022::day_10;


TEST(day_10_part_1, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    EXPECT_EQ(part_1(iss), 13140);
}

TEST(day_10_part_2, puzzle_example) {
    std::istringstream iss{ puzzle_example_sv.data() };
    std::string_view expected_output{
        "##..##..##..##..##..##..##..##..##..##..\n"
        "###...###...###...###...###...###...###.\n"
        "####....####....####....####....####....\n"
        "#####.....#####.....#####.....#####.....\n"
        "######......######......######......####\n"
        "#######.......#######.......#######....."
    };
    EXPECT_EQ(part_2(iss), expected_output);
}

TEST(day_10_main, output) {
    std::ostringstream oss{};
    main(oss);
    std::string_view part_2_expected_output{
        "###..#.....##..####.#..#..##..####..##..\n"
        "#..#.#....#..#.#....#.#..#..#....#.#..#.\n"
        "#..#.#....#....###..##...#..#...#..#....\n"
        "###..#....#.##.#....#.#..####..#...#.##.\n"
        "#....#....#..#.#....#.#..#..#.#....#..#.\n"
        "#....####..###.#....#..#.#..#.####..###."
    };
    EXPECT_THAT(oss.str(), ::testing::HasSubstr(
        fmt::format(
            "Part 1: sum of signal strengths = 15880\n"
            "Part 2:\n{}\n",
            part_2_expected_output
        )
    ));
}
