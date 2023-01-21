#pragma once

#include <cstdint>  // int64_t
#include <iosfwd>
#include <range/v3/all.hpp>
#include <regex>
#include <string>  // getline
#include <string_view>
#include <vector>


namespace aoc_2022::day_15 {
    struct point {
        int x{ -1 };
        int y{ -1 };
        auto operator<=>(const point& other) const noexcept = default;
    };

    using manhattan_distance = int;
    [[nodiscard]] inline auto get_manhattan_distance(const point& from, const point& to) {
        return ((from.x < to.x) ? (to.x - from.x) : (from.x - to.x)) +
            ((from.y < to.y) ? (to.y - from.y) : (from.y - to.y));
    }

    struct sb{  // sensors and beacons
        point s{};
        point b{};
        manhattan_distance md{};

        sb(point s, point b)
            : s{ s }
            , b{ b }
            , md{ get_manhattan_distance(s, b) }
        {}
    };

    struct sb_map {
        std::vector<sb> sbs{};

        friend std::istream& operator>>(std::istream& is, sb_map& m) {
            for (std::string line{}; std::getline(is, line); ) {
                std::regex pattern{ R"(Sensor at x=(-?[0-9]+), y=(-?[0-9]+)"
                    ": closest beacon is at x=(-?[0-9]+), y=(-?[0-9]+))" };
                std::smatch matches{};
                if (std::regex_match(line, matches, pattern)) {
                    point s{ std::stoi(matches[1].str()), std::stoi(matches[2].str()) };
                    point b{ std::stoi(matches[3].str()), std::stoi(matches[4].str()) };
                    m.sbs.emplace_back(s, b);
                }
            }
            return is;
        }
    };

    struct interval {
        int start{};
        int end{};

        [[nodiscard]] auto contains(int x) const {
            return start <= x and x < end;
        }
        [[nodiscard]] auto contains(const interval& other) const {
            return start <= other.start and other.end <= end;
        }
        [[nodiscard]] friend auto operator<(const interval& lhs, const interval& rhs) noexcept {
            return lhs.start < rhs.start;
        }
    };

    struct intervals{
        std::vector<interval> data;

        void insert(interval i) {
            data.push_back(i);
        }
        void merge() {
            if (data.empty()) {
                return;
            }
            std::vector<interval> stack{};
            std::sort(data.begin(), data.end());
            stack.push_back(data[0]);
            for (size_t i{ 1 }; i < data.size(); ++i) {
                auto& top{ stack.back() };
                auto& current_interval{ data[i] };
                if (top.end < current_interval.start) {
                    stack.push_back(current_interval);
                } else if (top.end < current_interval.end) {
                    top.end = current_interval.end;
                }
            }
            data.assign(stack.begin(), stack.end());
        }
        [[nodiscard]] bool contain(int x) const {
            return ranges::any_of(data, [&x](const interval& i) { return i.contains(x);  });
        }
        [[nodiscard]] bool contain(const interval& i) const {
            return ranges::any_of(data, [&i](const interval& j) { return j.contains(i); });
        }
    };

    [[nodiscard]] inline auto get_sensor_range_intervals(const sb_map& m, int row) {
        intervals intervals{};
        ranges::for_each(m.sbs, [&intervals, &row](const sb& sb) {
            auto&& x{ sb.s.x };
            auto&& y{ sb.s.y };
            auto&& md{ sb.md };
            auto no_of_intersected_sensor_range_rows{ (y > row)
                ? ((y - md <= row) ? (row - (y - md) + 1) : 0)
                : ((y + md >= row) ? (y + md - row + 1) : 0)
            };
            if (no_of_intersected_sensor_range_rows > 0) {
                auto start_x{ x - no_of_intersected_sensor_range_rows + 1 };
                auto end_x{ x + no_of_intersected_sensor_range_rows };
                intervals.insert({ start_x, end_x });
            }
        });
        intervals.merge();
        return intervals;
    }

    inline static std::string_view puzzle_example_sv{
        "Sensor at x=2, y=18: closest beacon is at x=-2, y=15\n"
        "Sensor at x=9, y=16: closest beacon is at x=10, y=16\n"
        "Sensor at x=13, y=2: closest beacon is at x=15, y=3\n"
        "Sensor at x=12, y=14: closest beacon is at x=10, y=16\n"
        "Sensor at x=10, y=20: closest beacon is at x=10, y=16\n"
        "Sensor at x=14, y=17: closest beacon is at x=10, y=16\n"
        "Sensor at x=8, y=7: closest beacon is at x=2, y=10\n"
        "Sensor at x=2, y=0: closest beacon is at x=2, y=10\n"
        "Sensor at x=0, y=11: closest beacon is at x=2, y=10\n"
        "Sensor at x=20, y=14: closest beacon is at x=25, y=17\n"
        "Sensor at x=17, y=20: closest beacon is at x=21, y=22\n"
        "Sensor at x=16, y=7: closest beacon is at x=15, y=3\n"
        "Sensor at x=14, y=3: closest beacon is at x=15, y=3\n"
        "Sensor at x=20, y=1: closest beacon is at x=15, y=3"
    };

    long part_1(std::istream& puzzle_input_is, int row);
    std::int64_t part_2(std::istream& puzzle_input_is, int distress_area_width);
    void main(std::ostream& os);
}  // namespace aoc_2022::day_15
