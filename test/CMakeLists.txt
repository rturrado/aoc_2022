# Sources
set(test_sources
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
)
list(APPEND app_sources ${test_sources})


# Test executable
add_executable(${PROJECT_NAME}_test ${app_sources})
target_compile_features(${PROJECT_NAME}_test PRIVATE cxx_std_23)
target_link_libraries(${PROJECT_NAME}_test PRIVATE
    lib_${PROJECT_NAME}
    ${CONAN_LIBS}
)


# Target compile options
if(MSVC)
    set(msvc_compile_options
        /W3 /WX /w34996
        /D_CONSOLE /DCONSOLE
        /D_UNICODE /DUNICODE
        /diagnostics:column /EHsc /FC /fp:precise /Gd /GS /MP /sdl /utf-8 /Zc:inline
    )
    target_compile_options(${PROJECT_NAME} PRIVATE ${msvc_compile_options})
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    set(unixlike_compile_options
        -pedantic-errors -Werror -Wall -Wextra
        -Wl,-z,defs
        -Wno-deprecated
        # -Wconversion -Wsign-conversion -Wno-sign-conversion  # do not sort flags; order matters
    )
    target_compile_options(${PROJECT_NAME} PRIVATE ${unixlike_compile_options})
endif()
if(CODE_COVERAGE)
    if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        target_compile_options(${PROJECT_NAME}_test PRIVATE -fprofile-arcs -ftest-coverage)
        target_link_options(${PROJECT_NAME}_test PRIVATE -fprofile-arcs -ftest-coverage)
    endif()
endif()


# Shared libraries
if(WIN32)
    # Copy DLLs the target depends on
    add_custom_command(
        TARGET ${PROJECT_NAME}_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}_test> $<TARGET_FILE_DIR:${PROJECT_NAME}_test>
        COMMAND_EXPAND_LISTS
    )
elseif(UNIX)
    set_target_properties(${PROJECT_NAME}_test PROPERTIES
        SKIP_BUILD_RPATH FALSE
        BUILD_WITH_INSTALL_RPATH FALSE
        INSTALL_RPATH ""
        INSTALL_RPATH_USE_LINK_PATH FALSE
        LINK_FLAGS "-Wl,-rpath,'$ORIGIN/'"
        )
endif()


include(GoogleTest)
gtest_add_tests(TARGET ${PROJECT_NAME}_test
    SOURCES ${test_sources}
    EXTRA_ARGS ${PROJECT_SOURCE_DIR}/res
)
