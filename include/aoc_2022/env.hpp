#pragma once

#include <filesystem>


namespace aoc_2022 {
    class env {
    public:
        [[nodiscard]] static env& get_instance() {
            static env instance;
            return instance;
        }
        [[nodiscard]] auto get_resource_folder_path() {
            return resource_folder_path_;
        }
        void set_resource_folder_path(const std::filesystem::path& p) {
            resource_folder_path_ = p;
        }
    private:
        env() = default;
        std::filesystem::path resource_folder_path_{};
    };

    [[nodiscard]] inline auto get_puzzle_inputs_folder_path() {
        return env::get_instance().get_resource_folder_path() / "puzzle_inputs";
    }
}  // namespace aoc_2022
