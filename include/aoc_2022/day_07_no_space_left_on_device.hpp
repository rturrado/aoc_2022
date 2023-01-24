#pragma once

#include <iosfwd>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>


namespace aoc_2022::day_7 {
    using path_t = std::string;
    using dirs_t = std::unordered_map<path_t, int>;
    using dir_stack_t = std::vector<std::string>;

    inline static std::string_view puzzle_example_sv{
        "$ cd /\n"
        "$ ls\n"
        "dir a\n"
        "14848514 b.txt\n"
        "8504156 c.dat\n"
        "dir d\n"
        "$ cd a\n"
        "$ ls\n"
        "dir e\n"
        "29116 f\n"
        "2557 g\n"
        "62596 h.lst\n"
        "$ cd e\n"
        "$ ls\n"
        "584 i\n"
        "$ cd ..\n"
        "$ cd ..\n"
        "$ cd d\n"
        "$ ls\n"
        "4060174 j\n"
        "8033020 d.log\n"
        "5626152 d.ext\n"
        "7214296 k"
    };

    int part_1(std::istream& puzzle_input_is);
    int part_2(std::istream& puzzle_input_is);
    void puzzle_main(std::ostream& os);
}  // namespace aoc_2022::day_7
