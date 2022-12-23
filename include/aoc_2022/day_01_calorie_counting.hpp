#pragma once

#include <fmt/core.h>
#include <iosfwd>
#include <sstream>


namespace aoc_2022::day_1 {
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
}  // namespace aoc_2022::day_1


void puzzle_1_main(std::ostream& os);
