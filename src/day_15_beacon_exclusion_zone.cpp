#include "day_15_beacon_exclusion_zone.hpp"
#include "env.hpp"

#include <filesystem>
#include <fmt/ostream.h>
#include <unordered_set>

namespace fs = std::filesystem;


namespace aoc_2022::day_15 {
    long part_1(std::istream& puzzle_input_is, int row) {
        sb_map m{};
        puzzle_input_is >> m;
        intervals intervals{};
        auto positions_with_sensor{ m.sbs
            | ranges::views::transform(&sb::s)
            | ranges::views::filter([&row](const point& p) { return p.y == row; })
            | ranges::views::transform(&point::x)
            | ranges::to<std::unordered_set<int>>()
        };
        auto positions_with_beacon{ m.sbs
            | ranges::views::transform(&sb::b)
            | ranges::views::filter([&row](const point& p) { return p.y == row; })
            | ranges::views::transform(&point::x)
            | ranges::to<std::unordered_set<int>>()
        };
        ranges::for_each(m.sbs, [&intervals, &row](const sb& sb) {
            const auto& x{ sb.s.x };
            const auto& y{ sb.s.y };
            const auto& md{ sb.md };
            int no_of_intersected_sensor_range_rows{};
            if (y > row) {
                if (y - md <= row) {
                    no_of_intersected_sensor_range_rows = (row - (y - md) + 1);
                }
            } else if (y + md >= row) {
                no_of_intersected_sensor_range_rows = (y + md - row + 1);
            }
            if (no_of_intersected_sensor_range_rows > 0) {
                auto start_x{ x - no_of_intersected_sensor_range_rows + 1 };
                auto end_x{ x + no_of_intersected_sensor_range_rows };
                intervals.insert({ start_x, end_x });
            }
        });
        intervals.merge();
        auto no_of_positions_that_cannot_contain_a_beacon{  // in row 2'000'000
            ranges::accumulate(intervals.data, 0, [](int total, const interval& i) {
                return total + i.end - i.start;
            })
            - ranges::count_if(positions_with_sensor, [&intervals](int x) { return intervals.contain(x); })
            - ranges::count_if(positions_with_beacon, [&intervals](int x) { return intervals.contain(x); })
        };
        return no_of_positions_that_cannot_contain_a_beacon;
    }

    std::int64_t part_2(std::istream& puzzle_input_is, int distress_area_width) {
        sb_map m{};
        puzzle_input_is >> m;
        int distress_area_height{ distress_area_width };
        interval distress_area_interval{ 0, distress_area_width + 1 };
        std::int64_t tuning_frequency{ -1 };
        for (int y{ 0 }; y < distress_area_height + 1; ++y) {
            auto detected_area_intervals{ get_sensor_range_intervals(m, y) };
            // There can only be one or two intervals
            if (not detected_area_intervals.contain(distress_area_interval)) {
                std::int64_t x{};
                if (detected_area_intervals.data.size() == 1) {
                    if (detected_area_intervals.data[0].start <= 0) {
                        x = distress_area_width;
                    }
                } else {
                    x = detected_area_intervals.data[0].end;
                }
                tuning_frequency = x * 4'000'000 + y;
                break;
            }
        }
        return tuning_frequency;
    }

    void puzzle_main(std::ostream& os) {
        std::ifstream puzzle_input_ifs_1{ get_puzzle_inputs_folder_path() / "day_15_beacon_exclusion_zone.txt" };
        std::ifstream puzzle_input_ifs_2{ get_puzzle_inputs_folder_path() / "day_15_beacon_exclusion_zone.txt" };
        fmt::print(os, "Part 1: number of positions that cannot contain a beacon in row 2'000'000 = {}\n",
            part_1(puzzle_input_ifs_1, 2'000'000));
        fmt::print(os, "Part 2: tuning frequency = {}\n", part_2(puzzle_input_ifs_2, 4'000'000));
    }
}  // namespace aoc_2022::day_15
