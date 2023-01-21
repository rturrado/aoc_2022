#include "day_03_rucksack_reorganization.hpp"
#include "env.hpp"

#include <algorithm>  // sort
#include <cctype>  // islower
#include <filesystem>
#include <fmt/ostream.h>
#include <iterator>  // inserter
#include <range/v3/all.hpp>
#include <set>
#include <utility>  // pair
#include <vector>

namespace fs = std::filesystem;


namespace aoc_2022::day_3 {
    int part_1(std::istream& puzzle_input_is) {
        std::vector<std::string> rucksacks{ std::istream_iterator<std::string>{ puzzle_input_is }, {} };
        auto get_compartments = [](auto&& rucksack) {
            auto half_size{ rucksack.size() / 2 };
            return std::pair<std::string, std::string>{
                rucksack.substr(0, half_size),
                rucksack.substr(half_size)
            };
        };
        auto get_shared_item = [](auto&& compartments) {
            auto& c1{ compartments.first };
            auto& c2{ compartments.second };
            std::ranges::sort(c1);
            std::ranges::sort(c2);
            std::set<char> shared_items{};
            std::ranges::set_intersection(c1, c2, std::inserter(shared_items, shared_items.end()));
            return *std::cbegin(shared_items);
        };
        auto get_item_priority = [](unsigned char c) {
            return (std::islower(c))
                ? c - 'a' + 1
                : c - 'A' + 27;
        };
        auto sum_of_priorities = ranges::accumulate(rucksacks
            | ranges::views::transform(get_compartments)  // transform list of rucksacks into a list of pairs of rucksack compartments
            | ranges::views::transform(get_shared_item)  // item shared by a pair of rucksack compartments
            | ranges::views::transform(get_item_priority)
        , 0);
        return sum_of_priorities;
    }

    int part_2(std::istream& puzzle_input_is) {
        std::vector<std::string> rucksacks{ std::istream_iterator<std::string>{ puzzle_input_is }, {} };
        auto get_shared_item = [](auto&& rucksack_group) {
            auto&& c1{ rucksack_group[0] };
            auto&& c2{ rucksack_group[1] };
            auto&& c3{ rucksack_group[2] };
            std::ranges::sort(c1);
            std::ranges::sort(c2);
            std::ranges::sort(c3);
            std::set<char> c12{};
            std::set<char> c123{};
            std::ranges::set_intersection(c1, c2, std::inserter(c12, c12.end()));
            std::ranges::set_intersection(c12, c3, std::inserter(c123, c123.end()));
            return *std::begin(c123);
        };
        auto get_item_priority = [](unsigned char c) {
            return (std::islower(c))
                ? c - 'a' + 1
                : c - 'A' + 27;
        };
        auto sum_of_priorities = ranges::accumulate(rucksacks
            | ranges::views::chunk(3)  // transform list rucksacks into a list of groups of 3 rucksacks
            | ranges::views::transform(get_shared_item)  // item shared by a group of 3 rucksacks
            | ranges::views::transform(get_item_priority)
        , 0);
        return sum_of_priorities;
    }

    void main(std::ostream& os) {
        std::ifstream puzzle_input_ifs_1{ get_puzzle_inputs_folder_path() / "day_03_rucksack_reorganization.txt" };
        std::ifstream puzzle_input_ifs_2{ get_puzzle_inputs_folder_path() / "day_03_rucksack_reorganization.txt" };
        fmt::print(os, "Part 1: sum of priorities = {}\n", part_1(puzzle_input_ifs_1));
        fmt::print(os, "Part 2: sum of priorities = {}\n", part_2(puzzle_input_ifs_2));
    }
}  // namespace aoc_2022::day_3
