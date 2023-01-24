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

    void read_forest_rows_and_cols(std::istream& puzzle_input_is, forest_t& rows, forest_t& cols);
    size_t part_1(const forest_t& rows, const forest_t& cols);
    size_t part_2(const forest_t& rows, const forest_t& cols);
    void puzzle_main(std::ostream& os);
}  // namespace aoc_2022::day_8
