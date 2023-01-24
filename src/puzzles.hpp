#pragma once

#include "day_01_calorie_counting.hpp"
#include "day_02_rock_paper_scissors.hpp"
#include "day_03_rucksack_reorganization.hpp"
#include "day_04_camp_cleanup.hpp"
#include "day_05_supply_stacks.hpp"
#include "day_06_tuning_trouble.hpp"
#include "day_07_no_space_left_on_device.hpp"
#include "day_08_treetop_tree_house.hpp"
#include "day_09_rope_bridge.hpp"
#include "day_10_cathode-ray_tube.hpp"
#include "day_11_monkey_in_the_middle.hpp"
#include "day_12_hill_climbing_algorithm.hpp"
#include "day_13_distress_signal.hpp"
#include "day_14_regolith_reservoir.hpp"
#include "day_15_beacon_exclusion_zone.hpp"

#include <chrono>
#include <functional>  // function, invoke
#include <iostream>  // cout
#include <vector>

#undef NDEBUG
#include <cassert>

namespace aoc = aoc_2022;


class puzzles {
    using function_type = std::function<void()>;

public:
    [[nodiscard]] static puzzles& get_instance() {
        static puzzles instance;
        return instance;
    }
    [[nodiscard]] constexpr size_t size() const {
        return data_.size();
    }
    void execute(size_t i) {
        assert((i > 0) && (i <= data_.size()));
        std::invoke(data_[i - 1]);
    }

private:
    puzzles() = default;

    std::vector<function_type> data_{
        []() { aoc::day_1::puzzle_main(std::cout); },  // calorie counting
        []() { aoc::day_2::puzzle_main(std::cout); },  // rock, paper, scissors
        []() { aoc::day_3::puzzle_main(std::cout); },  // rucksack reorganization
        []() { aoc::day_4::puzzle_main(std::cout); },  // camp cleanup
        []() { aoc::day_5::puzzle_main(std::cout); },  // supply stacks
        []() { aoc::day_6::puzzle_main(std::cout); },  // tuning trouble
        []() { aoc::day_7::puzzle_main(std::cout); },  // no space left on device
        []() { aoc::day_8::puzzle_main(std::cout); },  // treetop tree house
        []() { aoc::day_9::puzzle_main(std::cout); },  // rope bridge
        []() { aoc::day_10::puzzle_main(std::cout); },  // cathode-ray tube
        []() { aoc::day_11::puzzle_main(std::cout); },  // monkey in the middle
        []() { aoc::day_12::puzzle_main(std::cout); },  // hill climbing algorithm
        []() { aoc::day_13::puzzle_main(std::cout); },  // distress signal
        []() { aoc::day_14::puzzle_main(std::cout); },  // regolith reservoir
        []() { aoc::day_15::puzzle_main(std::cout); },  // beacon exclusion zone
    };
};
