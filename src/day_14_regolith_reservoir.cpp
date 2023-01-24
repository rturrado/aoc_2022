#include "day_14_regolith_reservoir.hpp"
#include "env.hpp"

#include <filesystem>
#include <fmt/ostream.h>

namespace fs = std::filesystem;


namespace aoc_2022::day_14 {
    int part_1(std::istream& puzzle_input_is) {
        rock_paths rps{};
        puzzle_input_is >> rps;
        part_1_impl::cave_map map{ rps };
        auto units_of_sand{ map.simulate_falling_sand() };
        return units_of_sand;
    }

    int part_2(std::istream& puzzle_input_is) {
        rock_paths rps{};
        puzzle_input_is >> rps;
        part_2_impl::cave_map map{ rps };
        auto units_of_sand{ map.simulate_falling_sand() };
        return units_of_sand;
    }

    void puzzle_main(std::ostream& os) {
        std::ifstream puzzle_input_ifs_1{ get_puzzle_inputs_folder_path() / "day_14_regolith_reservoir.txt" };
        std::ifstream puzzle_input_ifs_2{ get_puzzle_inputs_folder_path() / "day_14_regolith_reservoir.txt" };
        fmt::print(os, "Part 1: units of sand = {}\n", part_1(puzzle_input_ifs_1));
        fmt::print(os, "Part 2: units of sand = {}\n", part_2(puzzle_input_ifs_2));
    }
}  // namespace aoc_2022::day_14
