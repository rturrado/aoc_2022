#pragma once

#include <iosfwd>
#include <sstream>  // istringstream
#include <string>
#include <string_view>
#include <variant>
#include <vector>


namespace aoc_2022::day_13 {
    class packet {
    private:
        struct packet_element {
            using int_t = int;
            using list_of_elements_t = std::vector<packet_element>;

            std::variant<int_t, list_of_elements_t> data;

            [[nodiscard]]  bool operator==(const packet_element& other) const noexcept {
                // Both ints
                if (std::holds_alternative<int_t>(data) && std::holds_alternative<int_t>(other.data)) {
                    return std::get<int_t>(data) == std::get<int_t>(other.data);
                }
                // Both lists
                if (std::holds_alternative<list_of_elements_t>(data) && std::holds_alternative<list_of_elements_t>(other.data)) {
                    return std::get<list_of_elements_t>(data) == std::get<list_of_elements_t>(other.data);
                }
                // Int and list
                if (std::holds_alternative<int_t>(data) && !std::holds_alternative<int_t>(other.data)) {
                    return packet_element{ list_of_elements_t{ { std::get<int_t>(data) } } } == other;
                }
                // List and int
                if (not std::holds_alternative<int_t>(data) && std::holds_alternative<int_t>(other.data)) {
                    return *this == packet_element{ list_of_elements_t{ { std::get<int_t>(other.data) } } };
                }
                return false;
            }
            [[nodiscard]] bool operator<(const packet_element& other) const noexcept {
                // Both ints
                if (std::holds_alternative<int_t>(data) && std::holds_alternative<int_t>(other.data)) {
                    return std::get<int_t>(data) < std::get<int_t>(other.data);
                }
                // Both lists
                if (std::holds_alternative<list_of_elements_t>(data) && std::holds_alternative<list_of_elements_t>(other.data)) {
                    return std::get<list_of_elements_t>(data) < std::get<list_of_elements_t>(other.data);
                }
                // Int and list
                if (std::holds_alternative<int_t>(data) && !std::holds_alternative<int_t>(other.data)) {
                    return packet_element{ list_of_elements_t{ { std::get<int_t>(data) } } } < other;
                }
                // List and int
                if (not std::holds_alternative<int_t>(data) && std::holds_alternative<int_t>(other.data)) {
                    return *this < packet_element{ list_of_elements_t{ { std::get<int_t>(other.data) } } };
                }
                return false;
            }
        };
        [[nodiscard]] std::vector<packet_element> parse_list_of_packet_elements(std::istringstream& text_iss) const {
            std::vector<packet_element> ret{};
            char open_bracket{};
            text_iss >> open_bracket;
            for (;;) {
                char next_char{ static_cast<char>(text_iss.peek()) };
                if (next_char == '[') {
                    ret.push_back(packet_element{ parse_list_of_packet_elements(text_iss) });
                } else if (next_char == ']') {
                    char close_bracket{};
                    text_iss >> close_bracket;
                    break;
                } else if (next_char == ',') {
                    char comma{};
                    text_iss >> comma;
                    continue;
                } else {  // number
                    int number{};
                    text_iss >> number;
                    ret.push_back(packet_element{ number });
                }
            }
            return ret;
        }
        std::vector<packet_element> content{};
    public:
        explicit packet(std::string text) {
            std::istringstream text_iss{ std::move(text) };
            content = parse_list_of_packet_elements(text_iss);
        }
        [[nodiscard]] bool operator==(const packet& other) const noexcept {
            return content == other.content;
        }
        [[nodiscard]] bool operator<(const packet& other) const noexcept {
            return content < other.content;
        }
    };

    inline static std::string_view puzzle_example_sv{
        "[1,1,3,1,1]\n"
        "[1,1,5,1,1]\n"
        "\n"
        "[[1],[2,3,4]]\n"
        "[[1],4]\n"
        "\n"
        "[9]\n"
        "[[8,7,6]]\n"
        "\n"
        "[[4,4],4,4]\n"
        "[[4,4],4,4,4]\n"
        "\n"
        "[7,7,7,7]\n"
        "[7,7,7]\n"
        "\n"
        "[]\n"
        "[3]\n"
        "\n"
        "[[[]]]\n"
        "[[]]\n"
        "\n"
        "[1,[2,[3,[4,[5,6,7]]]],8,9]\n"
        "[1,[2,[3,[4,[5,6,0]]]],8,9]"
    };

    int part_1(std::istream& puzzle_input_is);
    long part_2(std::istream& puzzle_input_is);
    void puzzle_main(std::ostream& os);
}  // namespace aoc_2022::day_13
