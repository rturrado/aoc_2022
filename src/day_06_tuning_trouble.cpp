#include "day_06_tuning_trouble.hpp"
#include "env.hpp"

#include <filesystem>
#include <fmt/ostream.h>
#include <range/v3/all.hpp>
#include <unordered_set>

namespace fs = std::filesystem;


namespace aoc_2022::day_6 {
    size_t get_start_of_marker(const std::string& buffer, size_t marker_size) {
        auto is_start_marker = [&marker_size](auto&& m) {
            return std::unordered_set<char>{ m.begin(), m.end() }.size() == marker_size;
        };
        return marker_size + ranges::distance(buffer
            | ranges::views::sliding(marker_size)
            | ranges::views::take_while([&is_start_marker](auto&& marker) {
                return !is_start_marker(marker);
            })
        );
    }

    size_t get_start_of_packet_marker(const std::string& buffer) {
        return get_start_of_marker(buffer, packet_marker_size);
    }

    size_t get_start_of_message_marker(const std::string& buffer) {
        return get_start_of_marker(buffer, message_marker_size);
    }

    size_t part_1(std::istream& puzzle_input_is) {
        std::string buffer{ std::istreambuf_iterator{ puzzle_input_is }, {} };
        return get_start_of_packet_marker(buffer);
    }

    size_t part_2(std::istream& puzzle_input_is) {
        std::string buffer{ std::istreambuf_iterator{ puzzle_input_is }, {} };
        return get_start_of_message_marker(buffer);
    }

    void puzzle_main(std::ostream& os) {
        std::ifstream puzzle_input_ifs_1{ get_puzzle_inputs_folder_path() / "day_06_tuning_trouble.txt" };
        std::ifstream puzzle_input_ifs_2{ get_puzzle_inputs_folder_path() / "day_06_tuning_trouble.txt" };
        fmt::print(os, "Part 1: start of packet marker = {}\n", part_1(puzzle_input_ifs_1));
        fmt::print(os, "Part 2: start of message marker = {}\n", part_2(puzzle_input_ifs_2));
    }
}  // namespace aoc_2022::day_6
