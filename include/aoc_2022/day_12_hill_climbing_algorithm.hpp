#pragma once

#include <deque>
#include <fmt/core.h>
#include <iosfwd>
#include <limits>
#include <range/v3/all.hpp>
#include <string>
#include <string_view>
#include <vector>  // erase_if

namespace aoc_2022::day_12 {
    struct position {
        int x{ -1 };
        int y{ -1 };
        friend bool operator==(const position& p1, const position& p2) noexcept = default;
    };

    enum class direction { up, down };

    class elevation_map {
    private:
        [[nodiscard]] auto get_position_1d(position p) const {
            return p.x * width_ + p.y;
        }
        [[nodiscard]] auto get_next_positions(const position& p) const {
            std::vector<position> ret{
                { p.x - 1, p.y },
                { p.x + 1, p.y },
                { p.x, p.y - 1 },
                { p.x, p.y + 1 }
            };
            std::erase_if(ret, [&p, this](const position& next_point_position) {
                auto& [i, j]{ next_point_position };
                return i < 0 || j < 0 || i >= height_ || j >= width_;
            });
            return ret;
        }
        [[nodiscard]] auto is_valid_movement(const position& from, const position& to, direction d) const {
            auto elevation_from{ points_[get_position_1d(from)] };
            auto elevation_to{ points_[get_position_1d(to)] };
            return (d == direction::up && elevation_to <= elevation_from + 1)
                || (d == direction::down && elevation_to >= elevation_from - 1);
        }
    public:
        explicit elevation_map(std::istream& is) {
            std::string row{};
            is >> row;
            width_ = static_cast<int>(row.size());
            do {
                height_++;
                points_ += row;
            } while (is >> row);
            start_ = find('S');
            end_ = find('E');
            points_[get_position_1d(start_)] = 'a';
            points_[get_position_1d(end_)] = 'z';
        }
        [[nodiscard]] auto get_start() const {
            return start_;
        }
        [[nodiscard]] auto get_end() const {
            return end_;
        }
        [[nodiscard]] auto get_shortest_path_size(const position& src, const position& dst, direction d) const {
            struct queue_item {
                position pos{};
                int distance_from_source{};
            };
            auto ret{ std::numeric_limits<int>::max() };
            std::vector<bool> visited(points_.size());  // visited points
            visited[get_position_1d(src)] = true;
            std::deque<queue_item> queue{};  // Breadth First Search queue
            queue.push_back({ src, 0 });
            while (not queue.empty()) {
                auto current_item{ queue.front() };
                const auto& current_position{ current_item.pos };
                const auto current_distance_from_source{ current_item.distance_from_source };
                queue.pop_front();
                if (current_position == dst) {
                    ret = current_distance_from_source;
                    break;
                }
                for (auto&& next_position : get_next_positions(current_item.pos)) {
                    auto next_position_1d{ get_position_1d(next_position) };
                    if (not visited[next_position_1d] && is_valid_movement(current_position, next_position, d)) {
                        queue.push_back({ next_position, current_distance_from_source + 1 });
                        visited[next_position_1d] = true;
                    }
                }
            }
            return ret;
        }
        [[nodiscard]] auto get_shortest_path_size(const position& src, const char dst, direction d) const {
            struct queue_item {
                position pos{};
                int distance_from_source{};
            };
            auto ret{ std::numeric_limits<int>::max() };
            std::vector<bool> visited(points_.size());  // visited points
            visited[get_position_1d(src)] = true;
            std::deque<queue_item> queue{};  // Breadth First Search queue
            queue.push_back({ src, 0 });
            while (not queue.empty()) {
                auto current_item{ queue.front() };
                const auto& current_position{ current_item.pos };
                const auto current_distance_from_source{ current_item.distance_from_source };
                queue.pop_front();
                if (points_[get_position_1d(current_position)] == dst) {
                    ret = current_distance_from_source;
                    break;
                }
                for (auto&& next_position : get_next_positions(current_item.pos)) {
                    auto next_position_1d{ get_position_1d(next_position) };
                    if (not visited[next_position_1d] && is_valid_movement(current_position, next_position, d)) {
                        queue.push_back({ next_position, current_distance_from_source + 1 });
                        visited[next_position_1d] = true;
                    }
                }
            }
            return ret;
        }
        [[nodiscard]] position find(char c) const {
            position ret{};
            if (auto pos{ points_.find(c) }; pos != std::string::npos) {
                ret.x = static_cast<int>(pos) / width_;
                ret.y = static_cast<int>(pos) % width_;
            }
            return ret;
        }
    private:
        std::string points_{};
        int width_{};
        int height_{};
        position start_{};
        position end_{};
    };

    inline static std::string_view puzzle_example_sv{
        "Sabqponm\n"
        "abcryxxl\n"
        "accszExk\n"
        "acctuvwj\n"
        "abdefghi"
    };

    int part_1(std::istream& puzzle_input_is);
    int part_2(std::istream& puzzle_input_is);
    void puzzle_main(std::ostream& os);
}  // namespace aoc_2022::day_12
