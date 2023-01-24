#include "day_01_calorie_counting.hpp"
#include "env.hpp"

#include <filesystem>
#include <fmt/ostream.h>

namespace fs = std::filesystem;


namespace aoc_2022::day_1 {
    void part_1(std::ostream& os, const fs::path& puzzle_input) {
        std::ifstream ifs{ puzzle_input };
        fmt::print(os, "Unimplemented\n");
    }


    void part_2(std::ostream& os, const fs::path& puzzle_input) {
        std::ifstream ifs{ puzzle_input };
        fmt::print(os, "Unimplemented\n");
    }

    void puzzle_main(std::ostream& os) {
        fs::path puzzle_input{ get_puzzle_inputs_folder_path() / "day_01_calorie_counting.txt" };
        part_1(os, puzzle_input);
        part_2(os, puzzle_input);
    }
}  // namespace aoc_2022::day_1
