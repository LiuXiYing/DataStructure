cmake_minimum_required(VERSION 3.20)
project(Lab12 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lab12_tree main.cpp)

enable_testing()
add_test(NAME tree COMMAND lab12_tree)
set_tests_properties(tree PROPERTIES
    PASS_REGULAR_EXPRESSION "tree tests: 12/12 passed"
)
