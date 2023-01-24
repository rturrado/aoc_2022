#include "day_12_hill_climbing_algorithm.hpp"
#include "env.hpp"

#include <filesystem>
#include <fmt/ostream.h>
#include <istream>

namespace fs = std::filesystem;


namespace aoc_2022::day_12 {
    int part_1(std::istream& puzzle_input_is) {
        elevation_map map{ puzzle_input_is };
        auto fewest_steps{ map.get_shortest_path_size(map.get_start(), map.get_end(), direction::up) };
        return fewest_steps;
    }

    int part_2(std::istream& puzzle_input_is) {
        elevation_map map{ puzzle_input_is };
        auto fewest_steps{ map.get_shortest_path_size(map.get_end(), 'a', direction::down) };
        return fewest_steps;
    }

    void puzzle_main(std::ostream& os) {
        std::ifstream puzzle_input_ifs_1{ get_puzzle_inputs_folder_path() / "day_12_hill_climbing_algorithm.txt" };
        std::ifstream puzzle_input_ifs_2{ get_puzzle_inputs_folder_path() / "day_12_hill_climbing_algorithm.txt" };
        fmt::print(os, "Part 1: fewest steps = {}\n", part_1(puzzle_input_ifs_1));
        fmt::print(os, "Part 2: fewest steps = {}\n", part_2(puzzle_input_ifs_2));
    }
}  // namespace aoc_2022::day_12
