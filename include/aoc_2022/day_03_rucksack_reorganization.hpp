#pragma once

#include <iosfwd>
#include <string_view>
#include <vector>


namespace aoc_2022::day_3 {
    [[maybe_unused]] inline static std::string_view puzzle_example_sv{
        "vJrwpWtwJgWrhcsFMMfFFhFp\n"
        "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL\n"
        "PmmdzqPrVvPwwTWBwg\n"
        "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn\n"
        "ttgJtRGJQctTZtZT\n"
        "CrZsJsPPZsGzwwsLwLmpwMDw\n"
    };

    int part_1(std::istream& puzzle_input_is);
    int part_2(std::istream& puzzle_input_is);
    void main(std::ostream& os);
}  // namespace aoc_2022::day_3
