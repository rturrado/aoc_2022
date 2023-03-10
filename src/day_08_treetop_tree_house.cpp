#include "day_08_treetop_tree_house.hpp"
#include "env.hpp"

#include <algorithm>  // any_of
#include <filesystem>
#include <fmt/ostream.h>
#include <iterator>  // istream_iterator
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace fs = std::filesystem;


namespace aoc_2022::day_8 {
    auto tree_is_tallest_from(auto&& trees, const char tree) {
        return !std::ranges::any_of(trees, [&tree](char t) { return t >= tree; });
    }
    auto tree_is_visible(const forest_t& rows, const forest_t& cols, size_t i, size_t j) {
        auto current_tree{ rows[i][j] };
        return tree_is_tallest_from(rows[i] | ranges::views::take_exactly(j), current_tree)  // left
            || tree_is_tallest_from(rows[i] | ranges::views::drop_exactly(j + 1), current_tree)  // right
            || tree_is_tallest_from(cols[j] | ranges::views::take_exactly(i), current_tree)  // top
            || tree_is_tallest_from(cols[j] | ranges::views::drop_exactly(i + 1), current_tree);  // bottom
    }
    auto distance_to_not_shorter_tree(auto&& trees, const char tree) {
        auto it{ std::ranges::find_if(trees, [&tree](char t) { return t >= tree; }) };
        return it == std::end(trees)
            ? std::ssize(trees)
            : std::distance(std::begin(trees), std::next(it));
    }
    auto get_scenic_score(const trees_t& row, const trees_t& col, size_t i, size_t j) {
        auto current_tree{ row[j] };
        const auto& trees_to_the_left{ row | ranges::views::take_exactly(j) | ranges::views::reverse };
        const auto& trees_to_the_right{ row | ranges::views::drop_exactly(j + 1) };
        const auto& trees_to_the_top{ col | ranges::views::take_exactly(i) | ranges::views::reverse };
        const auto& trees_to_the_bottom{ col | ranges::views::drop_exactly(i + 1) };
        return distance_to_not_shorter_tree(trees_to_the_left, current_tree)
            * distance_to_not_shorter_tree(trees_to_the_right, current_tree)
            * distance_to_not_shorter_tree(trees_to_the_top, current_tree)
            * distance_to_not_shorter_tree(trees_to_the_bottom, current_tree);
    }

    void read_forest_rows_and_cols(std::istream& puzzle_input_is, forest_t& rows, forest_t& cols) {
        rows = forest_t{ std::istream_iterator<std::string>{ puzzle_input_is }, {} };
        cols = forest_t(rows[0].size(), trees_t(rows.size(), '0'));
        const auto& row_indices{ ranges::views::iota(static_cast<size_t>(0), rows.size()) };
        const auto& col_indices{ ranges::views::iota(static_cast<size_t>(0), rows[0].size()) };
        ranges::for_each(ranges::views::cartesian_product(row_indices, col_indices),
        [&rows, &cols](const std::tuple<size_t, size_t>& t) {
            auto [i, j]{ t };
            cols[j][i] = rows[i][j];
        });
    }

    size_t part_1(const forest_t& rows, const forest_t& cols) {
        const auto& row_indices{ ranges::views::iota(static_cast<size_t>(0), rows.size()) };
        const auto& col_indices{ ranges::views::iota(static_cast<size_t>(0), cols.size()) };
        size_t no_of_visible_trees{ ranges::count_if(
            ranges::views::cartesian_product(row_indices, col_indices),
            [&rows, &cols](const std::tuple<size_t, size_t>& t) {
                auto [i, j]{ t };
                return tree_is_visible(rows, cols, i, j);
            }
        )};
        return no_of_visible_trees;
    }

    size_t part_2(const forest_t& rows, const forest_t& cols) {
        const auto& row_indices{ ranges::views::iota(static_cast<size_t>(0), rows.size()) };
        const auto& col_indices{ ranges::views::iota(static_cast<size_t>(0), cols.size()) };
        const auto& scenic_scores{ ranges::views::cartesian_product(row_indices, col_indices)
            | ranges::views::transform(
                [&rows, &cols](const std::tuple<size_t, size_t>& t) {
                    auto [i, j]{ t };
                    return get_scenic_score(rows[i], cols[j], i, j);
                }
        )};
        auto highest_scenic_score{ *ranges::max_element(scenic_scores) };
        return highest_scenic_score;
    }

    void puzzle_main(std::ostream& os) {
        std::ifstream puzzle_input_ifs{ get_puzzle_inputs_folder_path() / "day_08_treetop_tree_house.txt" };
        forest_t rows{};
        forest_t cols{};
        read_forest_rows_and_cols(puzzle_input_ifs, rows, cols);
        fmt::print(os, "Part 1: number of visible trees = {}\n", part_1(rows, cols));
        fmt::print(os, "Part 2: highest scenic score = {}\n", part_2(rows, cols));
    }
}  // namespace aoc_2022::day_8
