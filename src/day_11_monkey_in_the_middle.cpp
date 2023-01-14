#include "day_11_monkey_in_the_middle.hpp"
#include "env.hpp"

#include <algorithm>  // sort
#include <filesystem>
#include <fmt/ostream.h>
#include <string>  // getline
#include <vector>

namespace fs = std::filesystem;


namespace aoc_2022::day_11 {
    std::vector<monkey> parse_input(std::istream& is) {
        std::vector<monkey> ret{};
        for (std::string line{}; std::getline(is, line);) {
            if (line.starts_with("Monkey ")) {
                monkey m{};
                is >> m;
                ret.push_back(std::move(m));
            }
        }
        return ret;
    }

    int part_1(std::istream& puzzle_input_is) {
        auto monkeys{ parse_input(puzzle_input_is) };
        int no_of_rounds{ 20 };
        std::vector<int> inspection_times(monkeys.size(), 0);
        while (no_of_rounds--) {
            for (size_t i{ 0 }; i < monkeys.size(); ++i) {
                auto& current_monkey{ monkeys[i] };
                auto& current_items{ current_monkey.items };
                inspection_times[i] += current_items.empty() ? 0 : static_cast<int>(std::ssize(current_items));
                for (size_t j{ 0 }; j < current_items.size(); ++j) {
                    auto [worry_level, monkey_to_throw_item_to] = current_monkey.inspect_item(j);
                    monkeys[monkey_to_throw_item_to].items.push_back(worry_level);
                }
                current_items.clear();
            }
        }
        std::ranges::sort(inspection_times, std::greater<>{});
        auto monkey_business_level{ inspection_times[0] * inspection_times[1] };
        return monkey_business_level;
    }

    void main(std::ostream& os) {
        std::ifstream puzzle_input_ifs{ get_puzzle_inputs_folder_path() / "day_11_monkey_in_the_middle.txt" };
        fmt::print(os, "Part 1: monkey business level = {}\n", part_1(puzzle_input_ifs));
    }
}  // namespace aoc_2022::day_11
