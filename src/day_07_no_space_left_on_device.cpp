#include "day_07_no_space_left_on_device.hpp"
#include "env.hpp"

#include <algorithm>  // min_element
#include <filesystem>
#include <fmt/ostream.h>
#include <functional>  // less
#include <numeric>  // accumulate
#include <ranges>

namespace fs = std::filesystem;


namespace aoc_2022::day_7 {
    dirs_t parse_input(std::istream& puzzle_input_is) {
        dirs_t dirs{};
        dir_stack_t current_dir{};
        auto current_path = [&current_dir]() {
            return fmt::format("{}", fmt::join(current_dir, ""));
        };
        auto trim_right = [](std::string& text) {
            text.erase(text.find_last_not_of("\r\n") + 1);
        };
        auto parse_output_line = [&dirs, &current_dir, &current_path, &trim_right](std::string line) {
            trim_right(line);
            if ((line == "$ ls") || line.starts_with("dir")) {
                return;
            } else if (line == "$ cd ..") {
                auto subdir_size{ dirs[current_path()] };
                current_dir.pop_back();
                dirs[current_path()] += subdir_size;
            } else if (line.starts_with("$ cd")) {
                auto dir_name{ line.substr(5) };
                dir_name += (dir_name == "/") ? "" : "/";
                current_dir.push_back(dir_name);
            } else {  // file
                std::istringstream line_iss{ line };
                int size{};
                line_iss >> size;
                dirs[current_path()] += size;
            }
        };
        // Process all the input stream
        // Then 'cd ..' until reaching '/'
        // because that will update some more directory sizes
        for (std::string line{}; std::getline(puzzle_input_is, line); ) {
            parse_output_line(std::move(line));
        }
        while (current_path() != std::string{ "/" }) {
            parse_output_line("$ cd ..");
        }
        return dirs;
    }

    int part_1(std::istream& puzzle_input_is) {
        auto dirs{ parse_input(puzzle_input_is) };
        const int max_size{ 100'000 };
        auto total_sizes = std::accumulate(dirs.cbegin(), dirs.cend(), 0,
            [&max_size](int total, const auto& dir_entry) {
                return total + (dir_entry.second <= max_size ? dir_entry.second : 0);
        });
        return total_sizes;
    }


    int part_2(std::istream& puzzle_input_is) {
        auto dirs{ parse_input(puzzle_input_is) };
        const int total_system_space{ 70'000'000 };
        const int min_unused_space{ 30'000'000 };
        auto current_used_space{ dirs.at("/") };
        auto current_unused_space{ total_system_space - current_used_space };
        auto min_space_to_free{ min_unused_space - current_unused_space };
        auto&& directories_bigger_than_min_space_to_free = dirs
            | std::views::filter([&min_space_to_free](const auto& dir_entry) {
                return dir_entry.second >= min_space_to_free;
        });
        auto size_of_smallest_directory_to_free = std::ranges::min_element(
            directories_bigger_than_min_space_to_free,
            std::less<>{},
            &dirs_t::value_type::second
        )->second;
        return size_of_smallest_directory_to_free;
    }

    void puzzle_main(std::ostream& os) {
        std::ifstream puzzle_input_ifs_1{ get_puzzle_inputs_folder_path() / "day_07_no_space_left_on_device.txt" };
        std::ifstream puzzle_input_ifs_2{ get_puzzle_inputs_folder_path() / "day_07_no_space_left_on_device.txt" };
        fmt::print(os, "Part 1: total sizes = {}\n", part_1(puzzle_input_ifs_1));
        fmt::print(os, "Part 2: size of smallest directory to free = {}\n", part_2(puzzle_input_ifs_2));
    }
}  // namespace aoc_2022::day_7
