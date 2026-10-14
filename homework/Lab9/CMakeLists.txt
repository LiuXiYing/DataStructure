cmake_minimum_required(VERSION 3.20)
project(Lab9 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lab9_queue main.cpp)
add_executable(lab9_round_robin round_robin.cpp)
add_executable(lab9_bank bank.cpp)

enable_testing()
add_test(NAME queue COMMAND lab9_queue)
add_test(NAME round_robin COMMAND lab9_round_robin)
add_test(NAME bank COMMAND lab9_bank)
set_tests_properties(bank PROPERTIES
    PASS_REGULAR_EXPRESSION "arrived=5, served=4, remaining=1"
)
