#pragma once

#include <iosfwd>
#include <string_view>
#include <utility>  // pair


namespace aoc_2022::day_4 {
    inline static std::string_view puzzle_example_sv{
        "2-4,6-8\n"
        "2-3,4-5\n"
        "5-7,7-9\n"
        "2-8,3-7\n"
        "6-6,4-6\n"
        "2-6,4-8\n"
    };

    struct section_assignment {
        int first;
        int last;
    };
    using pair_of_section_assignments = std::pair<section_assignment, section_assignment>;

    long part_1(std::istream& puzzle_input_is);
    long part_2(std::istream& puzzle_input_is);
    void main(std::ostream& os);
}  // namespace aoc_2022::day_4
