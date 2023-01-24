#include "day_09_rope_bridge.hpp"
#include "env.hpp"

#include <array>
#include <filesystem>
#include <fmt/ostream.h>

namespace fs = std::filesystem;


namespace aoc_2022::day_9 {
    size_t part_1(std::istream& puzzle_input_is) {
        position head{};
        position tail{};
        visited_positions_t visited_positions{};
        visited_positions.insert(tail.to_string());  // start position, "0,0"
        char direction{};
        int positions{};
        while (puzzle_input_is >> direction >> positions) {
            while (positions--) {
                head.move_one(direction);
                if (not adjacent_positions(head, tail)) {
                    tail.move_towards(head);
                    visited_positions.insert(tail.to_string());
                }
            }
        }
        return visited_positions.size();
    }

    size_t part_2(std::istream& puzzle_input_is) {
        // Knots
        constexpr const int no_of_knots{ 10 };
        std::array<position, no_of_knots> knots{};
        auto& head{ knots[0] };
        auto& tail{ knots[9] };
        auto previous_tail{ tail };
        // Visited positions
        visited_positions_t visited_positions{};
        visited_positions.insert(tail.to_string());  // start position, "0,0"
        // Moves
        auto tail_move_one = [&no_of_knots, &knots]() {
            for (size_t i{ 1 }; i < no_of_knots; ++i) {
                auto& current_knot{ knots[i] };
                const auto& previous_knot{ knots[i - 1] };
                if (not adjacent_positions(current_knot, previous_knot)) {
                    current_knot.move_towards(previous_knot);
                } else {
                    break;
                }
            }
        };
        char direction{};
        int positions{};
        while (puzzle_input_is >> direction >> positions) {
            while (positions--) {
                head.move_one(direction);
                tail_move_one();
                if (tail != previous_tail) {
                    visited_positions.insert(tail.to_string());
                    previous_tail = tail;
                }
            }
        }
        return visited_positions.size();
    }

    void puzzle_main(std::ostream& os) {
        std::ifstream puzzle_input_ifs_1{ get_puzzle_inputs_folder_path() / "day_09_rope_bridge.txt" };
        std::ifstream puzzle_input_ifs_2{ get_puzzle_inputs_folder_path() / "day_09_rope_bridge.txt" };
        fmt::print(os, "Part 1: number of visited positions = {}\n", part_1(puzzle_input_ifs_1));
        fmt::print(os, "Part 2: number of visited positions = {}\n", part_2(puzzle_input_ifs_2));
    }
}  // namespace aoc_2022::day_9
