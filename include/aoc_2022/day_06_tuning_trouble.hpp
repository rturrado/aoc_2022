#pragma once

#include <iosfwd>
#include <string_view>


namespace aoc_2022::day_6 {
    constinit const size_t packet_marker_size{ 4 };
    constinit const size_t message_marker_size{ 14 };

    inline static std::string_view puzzle_example_1_sv{ "mjqjpqmgbljsphdztnvjfqwrcgsmlb" };
    inline static std::string_view puzzle_example_2_sv{ "bvwbjplbgvbhsrlpgdmjqwftvncz" };
    inline static std::string_view puzzle_example_3_sv{ "nppdvjthqldpwncqszvftbrmjlhg" };
    inline static std::string_view puzzle_example_4_sv{ "nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg" };
    inline static std::string_view puzzle_example_5_sv{ "zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw" };

    size_t part_1(std::istream& puzzle_input_is);
    size_t part_2(std::istream& puzzle_input_is);
    void puzzle_main(std::ostream& os);
}  // namespace aoc_2022::day_6
