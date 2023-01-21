#pragma once

#include <iosfwd>
#include <string>
#include <string_view>
#include <vector>


namespace aoc_2022::day_5 {
    inline static std::string_view puzzle_example_sv{
        "move 1 from 2 to 1\n"
        "move 3 from 1 to 3\n"
        "move 2 from 2 to 1\n"
        "move 1 from 1 to 2"
    };

    using queues_t = std::vector<std::string>;

    inline static const queues_t puzzle_example_queues{
        { "ZN" },
        { "MCD" },
        { "P" }
    };
    inline static const queues_t puzzle_input_queues{
        { "FDBZTJRN" },
        { "RSNJH" },
        { "CRNJGZFQ" },
        { "FVNGRTQ" },
        { "LTQF" },
        { "QCWZBRGN"},
        { "FCLSNHM" },
        { "DNQMTJ" },
        { "PGS" }
    };

    std::string part_1(std::istream& puzzle_input_is, queues_t queues);
    std::string part_2(std::istream& puzzle_input_is,  queues_t queues);
    void main(std::ostream& os);
}  // namespace aoc_2022::day_5
