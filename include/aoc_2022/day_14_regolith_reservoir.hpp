#pragma once

#include <range/v3/all.hpp>
#include <regex>
#include <string>  // getline
#include <utility>  // pair
#include <vector>


namespace aoc_2022::day_14 {
    struct point {
        int x{ -1 };
        int y{ -1 };
        auto operator<=>(const point& other) const noexcept = default;
    };
    enum class point_content {
        air = '.',
        rock = '#',
        sand = 'o',
        source_of_sand = '+'
    };
    inline std::ostream& operator<<(std::ostream& os, const point_content& pc) {
        return os << static_cast<char>(pc);
    }
    using rock_path = std::vector<point>;
    using rock_paths = std::vector<rock_path>;

    inline std::istream& operator>>(std::istream& is, rock_path& rp) {
        std::string line{};
        std::getline(is, line);
        std::regex pattern{ R"(([0-9]+),([0-9]+))" };
        std::smatch matches{};
        while (std::regex_search(line, matches, pattern)) {
            rp.emplace_back(std::stoi(matches[2].str()), std::stoi(matches[1].str()));
            line = matches.suffix();
        }
        return is;
    }
    inline std::istream& operator>>(std::istream& is, rock_paths& rps) {
        do {
            rock_path rp{};
            is >> rp;
            rps.push_back(std::move(rp));
        } while (is);
        return is;
    }

    namespace part_1_impl {
        class cave_map {
        private:
            point default_pouring_point{ 0, 500 };
        private:
            int height_{};
            int width_{};
            point pouring_point_{ default_pouring_point };
            std::vector<point_content> points_{};
        public:
            [[nodiscard]] auto& get_point_content(const point& p) {
                return points_[p.x * width_ + p.y];
            }
            [[nodiscard]] auto get_point_content(const point& p) const {
                return points_[p.x * width_ + p.y];
            }
        private:
            [[nodiscard]] auto calculate_map_boundaries(const rock_paths& rps) const {
                auto&& x_coordinates{ rps
                    | ranges::views::join
                    | ranges::views::transform([](const point& p) { return p.x; })
                };
                auto&& y_coordinates{ rps
                    | ranges::views::join
                    | ranges::views::transform([](const point& p) { return p.y; })
                };
                auto min_x{ default_pouring_point.x };
                auto max_x{ *ranges::max_element(x_coordinates) };
                auto min_y{ *ranges::min_element(y_coordinates) };
                auto max_y{ *ranges::max_element(y_coordinates) };
                return std::pair<point, point>{ { min_x, min_y }, { max_x, max_y } };
            }
            void shift_pouring_point(int shift_y) {
                pouring_point_.y -= shift_y;
            }
            static void shift_rock_paths(rock_paths& rps, int shift_y) {
                ranges::for_each(rps, [&shift_y](rock_path& rp) {
                    ranges::transform(rp, rp.begin(),
                        [&shift_y](point& p) { return point{ p.x, p.y - shift_y };
                    });
                });
            }
            void fill_point(const point& p, point_content content) {
                get_point_content(p) = content;
            }
            void fill_horizontal_segment(const point& from, const point& to, point_content content) {
                for (auto y : ranges::views::iota(from.y, to.y + 1)) {
                    fill_point({ from.x, y }, content);
                }
            }
            void fill_vertical_segment(const point& from, const point& to, point_content content) {
                for (auto x : ranges::views::iota(from.x, to.x + 1)) {
                    fill_point({ x, from.y }, content);
                }
            }
            void fill_segment(const point& from, const point& to, point_content content) {
                if (from.x == to.x) {
                    if (from.y < to.y) {
                        fill_horizontal_segment(from, to, content);
                    } else {
                        fill_horizontal_segment(to, from, content);
                    }
                } else {  // from.y == to.y
                    if (from.x < to.x) {
                        fill_vertical_segment(from, to, content);
                    } else {
                        fill_vertical_segment(to, from, content);
                    }
                }
            }
            void fill_pouring_point() {
                fill_point(pouring_point_, point_content::source_of_sand);
            }
            void fill_rock_paths(const rock_paths& rps) {
                for (const auto& rp : rps) {
                    for (auto slide_of_two_points : rp | ranges::views::sliding(2)) {
                        auto from{ slide_of_two_points[0] };
                        auto to{ slide_of_two_points[1] };
                        fill_segment(from, to, point_content::rock);
                    }
                }
            }
        public:
            explicit cave_map(rock_paths& rps) {
                auto [top_left, bottom_down] = calculate_map_boundaries(rps);
                height_ = bottom_down.x - top_left.x + 1;
                width_ = bottom_down.y - top_left.y + 1;
                points_ = std::vector<point_content>(height_ * width_, point_content::air);

                auto shift_y{ top_left.y };
                shift_pouring_point(shift_y);
                shift_rock_paths(rps, shift_y);

                fill_pouring_point();
                fill_rock_paths(rps);
            }
            auto simulate_falling_sand() {
                auto point_is_free = [this](const auto& p) {
                    return get_point_content(p) == point_content::air;
                };
                auto point_is_valid = [this](const auto& p) {
                    return p.x >= 0 and p.x < height_ and p.y >= 0 and p.y < width_;
                };
                auto step = [&point_is_valid, &point_is_free](const auto& current_point) {
                    if (point next_point_down{ current_point.x + 1, current_point.y };
                        point_is_free(next_point_down)) {
                        return next_point_down;
                    }
                    point next_point_down_left{ current_point.x + 1, current_point.y - 1 };
                    if (not point_is_valid(next_point_down_left)) {
                        return point{};
                    } else if (point_is_free(next_point_down_left)) {
                        return next_point_down_left;
                    }
                    point next_point_down_right{ current_point.x + 1, current_point.y + 1 };
                    if (not point_is_valid(next_point_down_left)) {
                        return point{};
                    } else if (point_is_free(next_point_down_right)) {
                        return next_point_down_right;
                    }
                    return current_point;
                };
                int units_of_sand{};
                for (;;) {  // generating units of sand
                    point current_point{ pouring_point_ };
                    for (;;) {  // stepping each unit of sand
                        point next_point{ step(current_point) };
                        if (next_point == point{}) {  // falling into the endless void
                            return units_of_sand;
                        } else if (next_point == current_point) {  // rest
                            fill_point(current_point, point_content::sand);
                            break;
                        } else {  // continue falling
                            current_point = next_point;
                        }
                    }
                    units_of_sand++;
                }
            }
            friend std::ostream& operator<<(std::ostream& os, const cave_map& m) {
                auto&& lines{ m.points_ | ranges::views::chunk(m.width_) };
                for (auto&& line : lines) {
                    for (auto&& point : line) {
                        os << point;
                    }
                    os << "\n";
                }
                return os;
            }
        };
    }  // namespace part_1_impl

    namespace part_2_impl {
        class cave_map {
        private:
            point default_pouring_point{ 0, 500 };
            int extra_height{ 2 };  // blank row and floor
            int extra_width{ 300 };  // for the simulation of an infinite floor
        private:
            int height_{};
            int width_{};
            point pouring_point_{ default_pouring_point };
            std::vector<point_content> points_{};
        public:
            [[nodiscard]] auto& get_point_content(const point& p) {
                return points_[p.x * width_ + p.y];
            }
            [[nodiscard]] auto get_point_content(const point& p) const {
                return points_[p.x * width_ + p.y];
            }
        private:
            [[nodiscard]] auto calculate_map_boundaries(const rock_paths& rps) const {
                auto&& x_coordinates{ rps
                    | ranges::views::join
                    | ranges::views::transform([](const point& p) { return p.x; })
                };
                auto&& y_coordinates{ rps
                    | ranges::views::join
                    | ranges::views::transform([](const point& p) { return p.y; })
                };
                auto min_x{ default_pouring_point.x };
                auto max_x{ *ranges::max_element(x_coordinates) };
                auto min_y{ *ranges::min_element(y_coordinates) };
                auto max_y{ *ranges::max_element(y_coordinates) };
                return std::pair<point, point>{ { min_x, min_y }, { max_x, max_y } };
            }
            void shift_pouring_point(int shift_y) {
                pouring_point_.y -= shift_y;
            }
            static void shift_rock_paths(rock_paths& rps, int shift_y) {
                ranges::for_each(rps, [&shift_y](rock_path& rp) {
                    ranges::transform(rp, rp.begin(),
                        [&shift_y](point& p) { return point{ p.x, p.y - shift_y };
                    });
                });
            }
            void fill_point(const point& p, point_content content) {
                get_point_content(p) = content;
            }
            void fill_horizontal_segment(const point& from, const point& to, point_content content) {
                for (auto y : ranges::views::iota(from.y, to.y + 1)) {
                    fill_point({ from.x, y }, content);
                }
            }
            void fill_vertical_segment(const point& from, const point& to, point_content content) {
                for (auto x : ranges::views::iota(from.x, to.x + 1)) {
                    fill_point({ x, from.y }, content);
                }
            }
            void fill_segment(const point& from, const point& to, point_content content) {
                if (from.x == to.x) {
                    if (from.y < to.y) {
                        fill_horizontal_segment(from, to, content);
                    } else {
                        fill_horizontal_segment(to, from, content);
                    }
                } else {  // from.y == to.y
                    if (from.x < to.x) {
                        fill_vertical_segment(from, to, content);
                    } else {
                        fill_vertical_segment(to, from, content);
                    }
                }
            }
            void fill_pouring_point() {
                fill_point(pouring_point_, point_content::source_of_sand);
            }
            void fill_rock_paths(const rock_paths& rps) {
                for (const auto& rp : rps) {
                    for (auto slide_of_two_points : rp | ranges::views::sliding(2)) {
                        auto from{ slide_of_two_points[0] };
                        auto to{ slide_of_two_points[1] };
                        fill_segment(from, to, point_content::rock);
                    }
                }
            }
            void fill_floor() {
                fill_horizontal_segment({ height_ - 1, 0 }, { height_ - 1, width_ - 1 }, point_content::rock);
            }
        public:
            explicit cave_map(rock_paths& rps) {
                auto [top_left, bottom_down] = calculate_map_boundaries(rps);
                height_ = bottom_down.x - top_left.x + 1 + extra_height;
                width_ = bottom_down.y - top_left.y + 1 + extra_width;
                points_ = std::vector<point_content>(height_ * width_, point_content::air);

                auto shift_y{ top_left.y - extra_width / 2 };
                shift_pouring_point(shift_y);
                shift_rock_paths(rps, shift_y);

                fill_pouring_point();
                fill_rock_paths(rps);
                fill_floor();
            }
            auto simulate_falling_sand() {
                auto point_is_blocked_with = [this](const auto& p, point_content content) {
                    return get_point_content(p) == content;
                };
                auto point_is_free = [this](const auto& p) {
                    return get_point_content(p) == point_content::air;
                };
                auto step = [&point_is_free](const auto& current_point) {
                    if (point next_point_down{ current_point.x + 1, current_point.y };
                        point_is_free(next_point_down)) {
                        return next_point_down;
                    }
                    if (point next_point_down_left{ current_point.x + 1, current_point.y - 1 };
                        point_is_free(next_point_down_left)) {
                        return next_point_down_left;
                    }
                    if (point next_point_down_right{ current_point.x + 1, current_point.y + 1 };
                        point_is_free(next_point_down_right)) {
                        return next_point_down_right;
                    }
                    return current_point;
                };
                int units_of_sand{};
                while (not point_is_blocked_with(pouring_point_, point_content::sand)) {  // generating units of sand
                    point current_point{ pouring_point_ };
                    for (;;) {  // stepping each unit of sand
                        point next_point{ step(current_point) };
                        if (next_point == current_point) {  // rest
                            fill_point(current_point, point_content::sand);
                            break;
                        } else {  // continue falling
                            current_point = next_point;
                        }
                    }
                    units_of_sand++;
                }
                return units_of_sand;
            }
            friend std::ostream& operator<<(std::ostream& os, const cave_map& m) {
                auto&& lines{ m.points_ | ranges::views::chunk(m.width_) };
                for (auto&& line : lines) {
                    for (auto&& point : line) {
                        os << point;
                    }
                    os << "\n";
                }
                return os;
            }
        };
    }  // namespace part_2_impl

    inline static std::string_view puzzle_example_sv{
        "498,4 -> 498,6 -> 496,6\n"
        "503,4 -> 502,4 -> 502,9 -> 494,9"
    };

    int part_1(std::istream& puzzle_input_is);
    int part_2(std::istream& puzzle_input_is);
    void main(std::ostream& os);
}  // namespace aoc_2022::day_14
