#pragma once

#include <iosfwd>
#include <string_view>


namespace aoc_2022::day_2 {
    [[maybe_unused]] inline static std::string_view puzzle_example_sv{
        "A Y\n"
        "B X\n"
        "C Z\n"
    };

    [[nodiscard]] inline int calculate_round_score(int elf, int me) {
        int ret{};
        ret += (me + 1);  // rock (+1), paper (+2), scissors (+3)
        if (me == elf) {  // draw
            ret += 3;
        } else if ((me == elf + 1) or (me == elf - 2)) {  // win
            ret += 6;
        }
        // ret += 0;  // loss
        return ret;
    }

    [[nodiscard]] inline int calculate_my_strategy(int elf_strategy, int round_outcome) {
        int ret{};
        if (round_outcome == 1) {  // draw
            ret = elf_strategy;
        } else if (round_outcome == 0) {  // loss
            ret = (elf_strategy == 0)
                  ? 2
                  : (elf_strategy - 1);
        } else {  // win
            ret = (elf_strategy + 1) % 3;
        }
        return ret;
    }

    int part_1(std::istream& puzzle_input_is);
    int part_2(std::istream& puzzle_input_is);
    void main(std::ostream& os);
}  // namespace aoc_2022::day_2
