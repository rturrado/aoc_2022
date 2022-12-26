#include "env.hpp"
#include "puzzles.hpp"

#include <charconv>  // from_chars
#include <filesystem>
#include <fmt/ostream.h>
#include <iostream>  // cout
#include <string>  // getline

namespace fs = std::filesystem;
using namespace aoc_2022;


void print_usage(std::ostream& os) {
    fmt::print(os, "Usage:\n");
    fmt::print(os, "\taoc_2022 <RESOURCE_DIR_PATH>\n");
    fmt::print(os, "\n");
    fmt::print(os, "Where:\n");
    fmt::print(os, "\tRESOURCE_DIR_PATH  Path to the resource folder (relative or absolute)\n");
    fmt::print(os, "Example:\n");
    fmt::print(os, "\taoc_2022 ../res\n");
}


int main_impl(int argc, char** argv, std::istream& is, std::ostream& os) {
    if (argc != 2) {
        print_usage(os);
        return 1;
    }
    const fs::path resource_folder_path{ argv[1] };
    if (not fs::exists(resource_folder_path)) {
        fmt::print(os, "Error: path '{}' does not exist\n", resource_folder_path.generic_string());
        return 1;
    }
    if (not fs::is_directory(resource_folder_path)) {
        fmt::print(os, "Error: path '{}' is not a directory\n", resource_folder_path.generic_string());
        return 1;
    }
    env::get_instance().set_resource_folder_path(fs::absolute(resource_folder_path));

    auto& puzzles{ puzzles::get_instance() };

    try {
        while (true) {
            fmt::print(os,
                "What puzzle do you want to run? "
                "Please enter a number between {} and {} ('quit' to exit): ",
                1, puzzles.size());

            std::string input{};
            std::getline(is, input);
            if (input == "quit") {
                break;
            }

            size_t puzzle_number{};
            auto [ptr, ec]{ std::from_chars(input.data(), input.data() + input.size(), puzzle_number) };
            if (ec == std::errc{}) {
                if (1 <= puzzle_number and puzzle_number <= puzzles.size()) {
                    fmt::print(os, "\n[PUZZLE {}]\n", puzzle_number);
                    puzzles.execute(puzzle_number);
                    fmt::print("\n");
                } else {
                    fmt::print(os, "\tError: number not within the limits\n");
                }
            } else {
                fmt::print(os, "\tError: invalid input\n");
            }
        }
    } catch (const std::exception& ex) {
        fmt::print("Error: {}\n", ex.what());
        return 1;
    }
    return 0;
}


int main(int argc, char** argv) {
    return main_impl(argc, argv, std::cin, std::cout);
}
