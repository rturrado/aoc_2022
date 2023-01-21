#include "day_13_distress_signal.hpp"
#include "env.hpp"

#include <algorithm>  // find, sort
#include <filesystem>
#include <fmt/ostream.h>
#include <range/v3/all.hpp>
#include <string>  // getline
#include <utility>  // pair

namespace fs = std::filesystem;


namespace aoc_2022::day_13 {
    int part_1(std::istream& puzzle_input_is) {
        std::vector<std::pair<packet, packet>> pairs_of_packets{};
        do {
            std::string first_str{};
            std::string second_str{};
            std::string blank_line{};
            std::getline(puzzle_input_is, first_str);
            std::getline(puzzle_input_is, second_str);
            std::getline(puzzle_input_is, blank_line);
            pairs_of_packets.emplace_back(std::pair{ first_str, second_str });
        } while (puzzle_input_is);
        auto sum_of_indices_of_pairs_in_right_order{ ranges::accumulate(pairs_of_packets
            | ranges::views::enumerate
            | ranges::views::filter([](const auto& indexed_pair_of_packets) {
                const auto& pair_of_packets{ indexed_pair_of_packets.second };
                return pair_of_packets.first < pair_of_packets.second;
            })
            | ranges::views::transform([](const auto& pair) { return pair.first + 1; })
            , 0
        )};
        return sum_of_indices_of_pairs_in_right_order;
    }

    long part_2(std::istream& puzzle_input_is) {
        std::vector<packet> packets{};
        for (std::string line{}; std::getline(puzzle_input_is, line);) {
            if (not line.empty()) {
                packets.emplace_back(line);
            }
        }
        packet divider_packet_1("[[2]]");
        packet divider_packet_2("[[6]]");
        packets.push_back(divider_packet_1);
        packets.push_back(divider_packet_2);
        std::sort(packets.begin(), packets.end());
        auto index_1{ std::distance(packets.begin(), std::ranges::find(packets, divider_packet_1)) + 1 };
        auto index_2{ std::distance(packets.begin(), std::ranges::find(packets, divider_packet_2)) + 1 };
        auto decoder_key{ index_1 * index_2 };
        return decoder_key;
    }

    void main(std::ostream& os) {
        std::ifstream puzzle_input_ifs_1{ get_puzzle_inputs_folder_path() / "day_13_distress_signal.txt" };
        std::ifstream puzzle_input_ifs_2{ get_puzzle_inputs_folder_path() / "day_13_distress_signal.txt" };
        fmt::print(os, "Part 1: sum of indices of pairs in right order = {}\n", part_1(puzzle_input_ifs_1));
        fmt::print(os, "Part 2: decoder key = {}\n", part_2(puzzle_input_ifs_2));
    }
}  // namespace aoc_2022::day_13
