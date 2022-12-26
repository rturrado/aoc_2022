# Advent of Code 2022 (C++)
My solutions to the Advent of Code 2022 (C++).

## Installation

### Requirements

- **CMake**: required minimum version is 3.22.
- **conan**.
- **gcc**: this project has been tested with version 12.
- **git**.
- **ninja**.

From a `terminal`, as administrator:
```bash
$> sudo apt-get -qq update
$> sudo apt-get -qq upgrade
$> sudo apt-get -qq -y install \
       ccache \
       cmake \
       curl \
       g++-12 \
       gcc-12 \
       git \
       ninja-build \
       pkg-config \
       tar \
       unzip \
       wget \
       zip
$> sudo update-alternatives \
       --install /usr/bin/gcc gcc /usr/bin/gcc-12 100 \
       --slave /usr/bin/g++ g++ /usr/bin/g++-12 \
       --slave /usr/bin/gcov gcov /usr/bin/gcov-12
```

### Clone

From a `terminal`:
```bash
~/projects> git clone https://github.com/rturrado/aoc_2022
```

### Build

From a `terminal`:
```bash
conan install . -if=./cmake-build-unixlike-gcc-debug -pr=./conan/profiles/unixlike-gcc-debug-github --build=missing
```

### Run

From a `terminal`:
```bash
~/projects/aoc_2022> ./cmake-build-unixlike-gcc-debug/bin/aoc_2022 res
```
