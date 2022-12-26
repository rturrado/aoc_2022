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

using namespace aoc_2022;


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
        []() { day_1::main(std::cout); },  // calorie counting
        []() { day_2::main(std::cout); },  // rock, paper, scissors
/*
        []() { day_3::main(std::cout); },  // rucksack reorganization
        []() { day_4::main(std::cout); },  // camp cleanup
        []() { day_5::main(std::cout); },  // supply stacks
        []() { day_6::main(std::cout); },  // tuning trouble
        []() { day_7::main(std::cout); },  // no space left on device
        []() { day_8::main(std::cout); },  // treetop tree house
        []() { day_9::main(std::cout); },  // rope bridge
        []() { day_10::main(std::cout); },  // cathode-ray tube
        []() { day_11::main(std::cout); },  // monkey in the middle
        []() { day_12::main(std::cout); },  // hill climbing algorithm
        []() { day_13::main(std::cout); },  // distress signal
        []() { day_14::main(std::cout); },  // regolith reservoir
        []() { day_15::main(std::cout); },  // beacon exclusion zone
*/
    };
};
