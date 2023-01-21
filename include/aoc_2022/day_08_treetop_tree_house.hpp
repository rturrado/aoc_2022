#pragma once

#include <iosfwd>
#include <string>
#include <string_view>
#include <vector>


namespace aoc_2022::day_8 {
    using trees_t = std::string;
    using forest_t = std::vector<trees_t>;

    inline static std::string_view puzzle_example_sv{
        "30373\n"
        "25512\n"
        "65332\n"
        "33549\n"
        "35390"
    };

    size_t part_1(std::istream& puzzle_input_is);
    size_t part_2(std::istream& puzzle_input_is);
    void main(std::ostream& os);
}  // namespace aoc_2022::day_8
