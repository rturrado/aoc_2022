#pragma once

#include <functional>  // function, greater
#include <iosfwd>
#include <regex>  // regex_match, regex_search, smatch
#include <string>  // getline
#include <string_view>
#include <vector>


namespace aoc_2022::day_11 {
    struct monkey {
    private:
        struct monkey_to_throw_item_to_t {
            int when_test_is_true{};
            int when_test_is_false{};
        };

    public:
        monkey() = default;

        auto inspect_item(size_t i) {
            auto worry_level{ operation(items[i]) };
            worry_level /= 3;
            auto next_monkey{ (worry_level % divisor == 0)
                ? monkey_to_throw_item_to.when_test_is_true
                : monkey_to_throw_item_to.when_test_is_false
            };
            return std::pair<int, int>{ worry_level, next_monkey };
        }

        std::vector<int> items{};
        std::function<int(int)> operation{};
        int divisor{};
        monkey_to_throw_item_to_t monkey_to_throw_item_to{};

    private:
        friend void parse_starting_items_line(std::istream& is, monkey& m) {
            std::string line{};
            std::getline(is, line);
            std::smatch matches{};
            std::regex pattern{ "  Starting items: (.*)" };
            if (std::regex_match(line, matches, pattern)) {
                auto items_str{ matches[1].str() };
                std::regex items_pattern{ "([0-9]+)" };
                std::smatch items_matches{};
                while (std::regex_search(items_str, items_matches, items_pattern)) {
                    m.items.push_back(std::stoi(items_matches[1].str()));
                    items_str = items_matches.suffix();
                }
            }
        }
        friend void parse_operation_line(std::istream& is, monkey& m) {
            std::string line{};
            std::getline(is, line);
            std::smatch matches{};
            std::regex pattern{ R"(  Operation: new = old ([\+|\*]) (old|[0-9]+))" };
            if (std::regex_match(line, matches, pattern)) {
                auto operation_str{ matches[1].str() };
                auto operand_str{ matches[2].str() };
                if (operation_str == "*" and operand_str == "old") {
                    m.operation = [](int i) { return i * i; };
                } else if (operation_str == "*") {
                    m.operation = [operand=stoi(operand_str)](int i) { return i * operand; };
                } else if (operation_str == "+") {
                    m.operation = [operand=stoi(operand_str)](int i) { return i + operand; };
                }
            }
        }
        friend void parse_test_line(std::istream& is, monkey& m) {
            std::string line{};
            std::getline(is, line);
            std::smatch matches{};
            std::regex pattern{ "  Test: divisible by ([0-9]+)" };
            if (std::regex_match(line, matches, pattern)) {
                m.divisor = std::stoi(matches[1].str());
            }
        }
        friend void parse_if_true_line(std::istream& is, monkey& m) {
            std::string line{};
            std::getline(is, line);
            std::smatch matches{};
            std::regex pattern{ "    If true: throw to monkey ([0-9]+)" };
            if (std::regex_match(line, matches, pattern)) {
                m.monkey_to_throw_item_to.when_test_is_true = std::stoi(matches[1].str());
            }
        }
        friend void parse_if_false_line(std::istream& is, monkey& m) {
            std::string line{};
            std::getline(is, line);
            std::smatch matches{};
            std::regex pattern{ "    If false: throw to monkey ([0-9]+)" };
            if (std::regex_match(line, matches, pattern)) {
                m.monkey_to_throw_item_to.when_test_is_false = std::stoi(matches[1].str());
            }
        }
        friend std::istream& operator>>(std::istream& is, monkey& m) {
            parse_starting_items_line(is, m);
            parse_operation_line(is, m);
            parse_test_line(is, m);
            parse_if_true_line(is, m);
            parse_if_false_line(is, m);
            return is;
        }
    };

    inline static std::string_view puzzle_example_sv{
        "Monkey 0:\n"
        "  Starting items: 79, 98\n"
        "  Operation: new = old * 19\n"
        "  Test: divisible by 23\n"
        "    If true: throw to monkey 2\n"
        "    If false: throw to monkey 3\n"
        "\n"
        "Monkey 1:\n"
        "  Starting items: 54, 65, 75, 74\n"
        "  Operation: new = old + 6\n"
        "  Test: divisible by 19\n"
        "    If true: throw to monkey 2\n"
        "    If false: throw to monkey 0\n"
        "\n"
        "Monkey 2:\n"
        "  Starting items: 79, 60, 97\n"
        "  Operation: new = old * old\n"
        "  Test: divisible by 13\n"
        "    If true: throw to monkey 1\n"
        "    If false: throw to monkey 3\n"
        "\n"
        "Monkey 3:\n"
        "  Starting items: 74\n"
        "  Operation: new = old + 3\n"
        "  Test: divisible by 17\n"
        "    If true: throw to monkey 0\n"
        "    If false: throw to monkey 1"
    };

    int part_1(std::istream& puzzle_input_is);
    void puzzle_main(std::ostream& os);
}  // namespace aoc_2022::day_11
