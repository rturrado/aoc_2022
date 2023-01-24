#include "day_05_supply_stacks.hpp"
#include "env.hpp"

#include <algorithm>  // reverse
#include <filesystem>
#include <fmt/ostream.h>
#include <numeric>  // accumulate
#include <string>
#include <string_view>

namespace fs = std::filesystem;


namespace aoc_2022::day_5 {
    std::string part_1(std::istream& puzzle_input_is, queues_t queues) {
        int no_of_boxes{};
        int from_queue_index{};
        int to_queue_index{};
        for (std::string command_str{}, move{}, from{}, to{};
            puzzle_input_is >> move >> no_of_boxes >> from >> from_queue_index >> to >> to_queue_index; ) {

            auto& from_queue{ queues[from_queue_index - 1] };
            auto& to_queue{ queues[to_queue_index - 1] };
            auto from_queue_new_size{ from_queue.size() - no_of_boxes };
            auto from_boxes_to_move{ from_queue.substr(from_queue_new_size) };
            std::ranges::reverse(from_boxes_to_move);
            to_queue.append(from_boxes_to_move);
            from_queue.resize(from_queue_new_size);
        }
        auto message{ std::accumulate(queues.begin(), queues.end(), std::string{},
            [](const std::string& total, std::string_view queue) {
                return total + (queue.empty() ? char{} : queue.back());
            }
        )};
        return message;
    }

    std::string part_2(std::istream& puzzle_input_is, queues_t queues) {
        int no_of_boxes{};
        int from_queue_index{};
        int to_queue_index{};
        for (std::string command_str{}, move{}, from{}, to{};
             puzzle_input_is >> move >> no_of_boxes >> from >> from_queue_index >> to >> to_queue_index; ) {

            auto& from_queue{ queues[from_queue_index - 1] };
            auto& to_queue{ queues[to_queue_index - 1] };
            auto from_queue_new_size{ from_queue.size() - no_of_boxes };
            auto from_boxes_to_move{ from_queue.substr(from_queue_new_size) };
            to_queue.append(from_boxes_to_move);
            from_queue.resize(from_queue_new_size);
        }
        auto message{ std::accumulate(queues.begin(), queues.end(), std::string{},
            [](const std::string& total, std::string_view queue) {
                return total + (queue.empty() ? char{} : queue.back());
            }
        )};
        return message;
    }

    void puzzle_main(std::ostream& os) {
        std::ifstream puzzle_input_ifs_1{ get_puzzle_inputs_folder_path() / "day_05_supply_stacks.txt" };
        std::ifstream puzzle_input_ifs_2{ get_puzzle_inputs_folder_path() / "day_05_supply_stacks.txt" };
        fmt::print(os, "Part 1: message = {}\n", part_1(puzzle_input_ifs_1, puzzle_input_queues));
        fmt::print(os, "Part 2: message = {}\n", part_2(puzzle_input_ifs_2, puzzle_input_queues));
    }
}  // namespace aoc_2022::day_5
