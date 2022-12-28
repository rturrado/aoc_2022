from conans import ConanFile, CMake, tools


class Aoc2022Conan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    def requirements(self):
        self.requires("fmt/9.1.0")
        self.requires("range-v3/0.12.0")
        if tools.get_env("AOC_2022_BUILD_TESTS", True):
            self.requires("gtest/1.12.1")

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["ASAN_ENABLED"] = "ON" if tools.get_env("AOC_2022_BUILD_TESTS", True) else "OFF"
        cmake.definitions["AOC_2022_BUILD_TESTS"] = "ON" if tools.get_env("AOC_2022_BUILD_TESTS", True) else "OFF"
        cmake.definitions["AOC_2022_BUILD_BENCHMARKS"] = "ON" if tools.get_env("AOC_2022_BUILD_BENCHMARKS", True) else "OFF"
        if tools.get_env("CMAKE_C_COMPILER_LAUNCHER") is not None:
            cmake.definitions["CMAKE_C_COMPILER_LAUNCHER"] = tools.get_env("CMAKE_C_COMPILER_LAUNCHER")
        if tools.get_env("CMAKE_CXX_COMPILER_LAUNCHER") is not None:
            cmake.definitions["CMAKE_CXX_COMPILER_LAUNCHER"] = tools.get_env("CMAKE_CXX_COMPILER_LAUNCHER")
        cmake.definitions["CODE_COVERAGE"] = "ON" if tools.get_env("CODE_COVERAGE", True) else "OFF"
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
