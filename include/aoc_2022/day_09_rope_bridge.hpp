#pragma once

#include <algorithm>  // min, max
#include <fmt/format.h>
#include <iosfwd>
#include <string>  // getline
#include <string_view>
#include <unordered_set>


namespace aoc_2022::day_9 {
    struct position {
        int x{};
        int y{};

        void move_one(char direction) {
            if (direction == 'R') { x++; }
            else if (direction == 'L') { x--; }
            else if (direction == 'U') { y++; }
            else if (direction == 'D') { y--; }
        }
        void move_towards(const position& to) {
            auto move_x{ (to.x >= x) ? std::min(to.x - x, 1) : std::max(to.x - x, -1) };
            auto move_y{ (to.y >= y) ? std::min(to.y - y, 1) : std::max(to.y - y, -1) };
            x += move_x;
            y += move_y;
        }
        auto to_string() {
            return fmt::format("{},{}", x, y);
        }
        friend auto adjacent_positions(const position& p1, const position& p2) {
            auto diff_x{ (p1.x >= p2.x) ? p1.x - p2.x : p2.x - p1.x };
            auto diff_y{ (p1.y >= p2.y) ? p1.y - p2.y : p2.y - p1.y };
            return diff_x <= 1 && diff_y <= 1;
        };
        friend bool operator==(const position& p1, const position& p2) = default;
        friend bool operator!=(const position& p1, const position& p2) = default;
    };
    using visited_positions_t = std::unordered_set<std::string>;  // e.g. "13,21"

    inline static std::string_view puzzle_example_1_sv{
        "R 4\n"
        "U 4\n"
        "L 3\n"
        "D 1\n"
        "R 4\n"
        "D 1\n"
        "L 5\n"
        "R 2"
    };

    inline static std::string_view puzzle_example_2_sv{
        "R 5\n"
        "U 8\n"
        "L 8\n"
        "D 3\n"
        "R 17\n"
        "D 10\n"
        "L 25\n"
        "U 20"
    };

    size_t part_1(std::istream& puzzle_input_is);
    size_t part_2(std::istream& puzzle_input_is);
    void puzzle_main(std::ostream& os);
}  // namespace aoc_2022::day_9
