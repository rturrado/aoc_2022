#include "day_10_cathode-ray_tube.hpp"
#include "env.hpp"

#include <filesystem>
#include <fmt/ostream.h>
#include <numeric>  // exclusive_scan
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace fs = std::filesystem;


namespace aoc_2022::day_10 {
    std::vector<int> parse_input(std::istream& is) {
        std::vector<int> ret(240, 0);
        std::string instruction{};
        for (int i{ 0 }; is >> instruction;) {
            if (instruction == "noop") {
                ++i;
            } else {  // addx
                is >> ret[i + 1];
                i += 2;
            }
        }
        // noop| noop| noop| addx 3| addx 20|
        //    0|    0|    0| 0 | 3 | 0 | 20 |  0       <- ret
        //  (1)|    1|    1| 1 | 1 | 4 |  4 | 24 | 24  <- exclusive_scan(1)
        std::exclusive_scan(ret.begin(), ret.end(), ret.begin(), 1);
        return ret;
    }

    int part_1(std::istream& puzzle_input_is) {
        auto strengths{ parse_input(puzzle_input_is) };
        auto sum_of_signal_strengths{ ranges::accumulate(strengths
            | ranges::views::filter([i=0](int) mutable {
                ++i;
                return (i + 20) % 40 == 0;
            })  // 20, 60, 100, 140, 180, 220
            | ranges::views::transform([i=1](int v) mutable {
                auto ret{ v*i*20 };
                i += 2;
                return ret;
            })  // v*20, v*60...
            , 0
        )};
        return sum_of_signal_strengths;
    }

    std::string part_2(std::istream& puzzle_input_is) {
        auto sprite_positions{ parse_input(puzzle_input_is) };
        std::string crt(240, '.');
        auto is_sprite_at = [&sprite_positions](auto cycle) {
            auto sprite_pos{ sprite_positions[cycle] };
            auto pixel_pos{ cycle % 40 };
            return sprite_pos - 1 <= pixel_pos && pixel_pos <= sprite_pos + 1;
        };
        auto crt_rows{ crt
            | ranges::views::transform([cycle=0, &is_sprite_at](char) mutable {
                ++cycle;
                return is_sprite_at(cycle - 1) ? '#' : '.';
            })
            | ranges::views::chunk(40)
            | ranges::views::join('\n')
        };
        return fmt::format("{}", fmt::join(crt_rows, ""));
    }

    void puzzle_main(std::ostream& os) {
        std::ifstream puzzle_input_ifs_1{ get_puzzle_inputs_folder_path() / "day_10_cathode-ray_tube.txt" };
        std::ifstream puzzle_input_ifs_2{ get_puzzle_inputs_folder_path() / "day_10_cathode-ray_tube.txt" };
        fmt::print(os, "Part 1: sum of signal strengths = {}\n", part_1(puzzle_input_ifs_1));
        fmt::print(os, "Part 2:\n{}\n", part_2(puzzle_input_ifs_2));
    }
}  // namespace aoc_2022::day_10
