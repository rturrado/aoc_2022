#include "day_02_rock_paper_scissors.hpp"
#include "env.hpp"

#include <filesystem>
#include <fmt/ostream.h>

namespace fs = std::filesystem;


namespace aoc_2022::day_2 {
    int part_1(std::istream& puzzle_input_is) {
        char elf_strategy{};
        char my_strategy{};
        int total_score{};
        while (puzzle_input_is >> elf_strategy >> my_strategy) {
            total_score += calculate_round_score(elf_strategy - 'A', my_strategy - 'X');
        }
        return total_score;
    }

    int part_2(std::istream& puzzle_input_is) {
        char elf_strategy{};
        char round_outcome{};
        int total_score{};
        while (puzzle_input_is >> elf_strategy >> round_outcome) {
            int my_strategy{ calculate_my_strategy(elf_strategy - 'A', round_outcome - 'X') };
            total_score += calculate_round_score(elf_strategy - 'A', my_strategy);
        }
        return total_score;
    }

    void puzzle_main(std::ostream& os) {
        auto puzzle_input_path{ get_puzzle_inputs_folder_path() / "day_02_rock_paper_scissors.txt" };
        std::ifstream puzzle_input_ifs_1{ puzzle_input_path };
        std::ifstream puzzle_input_ifs_2{ puzzle_input_path };
        fmt::print(os, "Part 1: total score = {}\n", part_1(puzzle_input_ifs_1));
        fmt::print(os, "Part 2: total score = {}\n", part_2(puzzle_input_ifs_2));
    }
}  // namespace aoc_2022::day_2
