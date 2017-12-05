cmake_minimum_required(VERSION 3.8)
project(CSCPP C)

set(CMAKE_C_STANDARD 99)

find_package(BISON)
find_package(FLEX)

add_executable(yis)

add_executable(yas)

add_executable(hcl2c)