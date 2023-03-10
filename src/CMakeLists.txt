set(include_dir ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})


# Sources
set(lib_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/day_01_calorie_counting.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_02_rock_paper_scissors.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_03_rucksack_reorganization.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_04_camp_cleanup.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_05_supply_stacks.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_06_tuning_trouble.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_07_no_space_left_on_device.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_08_treetop_tree_house.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_09_rope_bridge.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_10_cathode-ray_tube.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_11_monkey_in_the_middle.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_12_hill_climbing_algorithm.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_13_distress_signal.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_14_regolith_reservoir.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/day_15_beacon_exclusion_zone.cpp"
)
set(app_sources
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/puzzles.hpp"
    )
list(APPEND app_sources ${lib_sources})


# Main library
add_library(lib_${PROJECT_NAME} ${lib_sources})
target_include_directories(lib_${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
set_target_properties(lib_${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME ${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}_${PROJECT_VERSION_MINOR}
)
target_compile_features(lib_${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(lib_${PROJECT_NAME} PUBLIC ${CONAN_LIBS})
if(CODE_COVERAGE)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        target_compile_options(lib_${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
        target_link_libraries(lib_${PROJECT_NAME} PRIVATE gcov)
        target_link_options(lib_${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
    endif()
endif()


# Main executable
add_executable(${PROJECT_NAME} ${app_sources})
target_include_directories(${PROJECT_NAME} PUBLIC
    "$<BUILD_INTERFACE:${include_dir}>"
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME} PRIVATE lib_${PROJECT_NAME})


# Target compile options
if(MSVC)
    set(msvc_compile_options
        /W3 /WX /w34996
        /D_CONSOLE /DCONSOLE
        /D_UNICODE /DUNICODE
        /diagnostics:column /EHsc /FC /fp:precise /Gd /GS /MP /sdl /utf-8 /Zc:inline
    )
    target_compile_options(lib_${PROJECT_NAME} PRIVATE ${msvc_compile_options})
    target_compile_options(${PROJECT_NAME} PRIVATE ${msvc_compile_options})
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    set(unixlike_compile_options
        -pedantic-errors -Werror -Wall -Wextra
        -Wl,-z,defs
        -Wno-deprecated
        # -Wconversion -Wsign-conversion -Wno-sign-conversion  # do not sort flags; order matters
    )
    target_compile_options(lib_${PROJECT_NAME} PRIVATE ${unixlike_compile_options})
    target_compile_options(${PROJECT_NAME} PRIVATE ${unixlike_compile_options})
endif()
if(CODE_COVERAGE)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
        target_link_options(${PROJECT_NAME} PRIVATE -fprofile-arcs -ftest-coverage)
    endif()
endif()
