#include "day_02_rock_paper_scissors.hpp"
#include "env.hpp"

#include <filesystem>
#include <fmt/ostream.h>
#include <fstream>

namespace fs = std::filesystem;


namespace aoc_2022::day_2 {
    void part_1(std::ostream& os, const fs::path& puzzle_input) {
        std::ifstream ifs{ puzzle_input };
        char elf_strategy{};
        char my_strategy{};
        int total_score{};
        while (ifs >> elf_strategy >> my_strategy) {
            total_score += calculate_round_score(elf_strategy - 'A', my_strategy - 'X');
        }
        fmt::print(os, "total score = {}\n", total_score);
    }


    void part_2(std::ostream& os, const fs::path& puzzle_input) {
        std::ifstream ifs{ puzzle_input };
        char elf_strategy{};
        char round_outcome{};
        int total_score{};
        while (ifs >> elf_strategy >> round_outcome) {
            int my_strategy{ calculate_my_strategy(elf_strategy - 'A', round_outcome - 'X') };
            total_score += calculate_round_score(elf_strategy - 'A', my_strategy);
        }
        fmt::print(os, "total score = {}\n", total_score);
    }

    void main(std::ostream& os) {
        fs::path puzzle_input{ get_puzzle_inputs_folder_path() / "day_02_rock_paper_scissors.txt" };
        part_1(os, puzzle_input);
        part_2(os, puzzle_input);
    }
}  // namespace aoc_2022::day_2
