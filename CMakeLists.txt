cmake_minimum_required(VERSION 3.8)
project(CSCPP C)

set(CMAKE_C_STANDARD 99)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

add_subdirectory(Chapter2)
add_subdirectory(Experiment1)
add_subdirectory(Experiment2)
add_subdirectory(Experiment3)