#include "day_04_camp_cleanup.hpp"
#include "env.hpp"

#include <filesystem>
#include <fmt/ostream.h>
#include <iterator>  // istream_iterator
#include <range/v3/all.hpp>
#include <sstream>  // istringstream
#include <vector>

namespace fs = std::filesystem;


namespace aoc_2022::day_4 {
    pair_of_section_assignments parse_pair_of_section_assignments(const std::string& pair_of_section_assignments_str) {
        section_assignment sa_1{};
        section_assignment sa_2{};
        char dash{};
        char comma{};
        std::istringstream pair_iss{ pair_of_section_assignments_str };
        pair_iss >> sa_1.first >> dash >> sa_1.last >> comma >> sa_2.first >> dash >> sa_2.last;
        return pair_of_section_assignments{ sa_1, sa_2 };
    }

    long part_1(std::istream& puzzle_input_is) {
        std::vector<std::string> pairs_of_section_assignments{ std::istream_iterator<std::string>{ puzzle_input_is }, {} };
        auto are_fully_contained = [](auto&& pair_of_section_assignments) {
            auto&& sa_1{ pair_of_section_assignments.first };
            auto&& sa_2{ pair_of_section_assignments.second };
            return
                ((sa_1.first <= sa_2.first) and (sa_1.last >= sa_2.last)) or
                ((sa_1.first >= sa_2.first) and (sa_1.last <= sa_2.last));
        };
        auto no_of_fully_contained_ranges = ranges::distance(pairs_of_section_assignments
            | ranges::views::transform(parse_pair_of_section_assignments)
            | ranges::views::filter(are_fully_contained));
        return no_of_fully_contained_ranges;
    }

    long part_2(std::istream& puzzle_input_is) {
        std::vector<std::string> pairs_of_section_assignments{ std::istream_iterator<std::string>{ puzzle_input_is }, {} };
        auto are_partially_contained = [](auto&& pair_of_section_assignments) {
            auto&& sa_1{ pair_of_section_assignments.first };
            auto&& sa_2{ pair_of_section_assignments.second };
            return not
                (((sa_1.first < sa_2.first) and (sa_1.last < sa_2.first)) or
                 ((sa_2.first < sa_1.first) and (sa_2.last < sa_1.first)));
        };
        auto no_of_partially_contained_ranges = ranges::distance(pairs_of_section_assignments
            | ranges::views::transform(parse_pair_of_section_assignments)
            | ranges::views::filter(are_partially_contained));
        return no_of_partially_contained_ranges;
    }

    void puzzle_main(std::ostream& os) {
        std::ifstream puzzle_input_ifs_1{ get_puzzle_inputs_folder_path() / "day_04_camp_cleanup.txt" };
        std::ifstream puzzle_input_ifs_2{ get_puzzle_inputs_folder_path() / "day_04_camp_cleanup.txt" };
        fmt::print(os, "Part 1: number of fully contained ranges = {}\n", part_1(puzzle_input_ifs_1));
        fmt::print(os, "Part 2: number of partially contained ranges = {}\n", part_2(puzzle_input_ifs_2));
    }
}  // namespace aoc_2022::day_4
