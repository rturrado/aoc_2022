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


class puzzles {
    using function_type = std::function<void()>;

public:
    [[nodiscard]] static puzzles& get_instance() {
        static puzzles instance;
        return instance;
    }
    [[nodiscard]] constexpr size_t size() {
        return data_.size();
    }
    void execute(size_t i) {
        assert((i > 0) && (i <= data_.size()));
        std::invoke(data_[i - 1]);
    }

private:
    puzzles() = default;

    std::vector<function_type> data_{
        []() { puzzle_1_main(std::cout); },  // calorie counting
/*
        []() { puzzle_2_main(std::cout); },  // rock, paper, scissors
        []() { puzzle_3_main(std::cout); },  // rucksack reorganization
        []() { puzzle_4_main(std::cout); },  // camp cleanup
        []() { puzzle_5_main(std::cout); },  // supply stacks
        []() { puzzle_6_main(std::cout); },  // tuning trouble
        []() { puzzle_7_main(std::cout); },  // no space left on device
        []() { puzzle_8_main(std::cout); },  // treetop tree house
        []() { puzzle_9_main(std::cout); },  // rope bridge
        []() { puzzle_10_main(std::cout); },  // cathode-ray tube
        []() { puzzle_11_main(std::cout); },  // monkey in the middle
        []() { puzzle_12_main(std::cout); },  // hill climbing algorithm
        []() { puzzle_13_main(std::cout); },  // distress signal
        []() { puzzle_14_main(std::cout); },  // regolith reservoir
        []() { puzzle_15_main(std::cout); },  // beacon exclusion zone
*/
    };
};
