cmake_minimum_required(VERSION 3.8)
project(CSCPP C)

set(CMAKE_C_STANDARD 99)
add_executable(myint myint.c)
add_executable(myspin myspin.c)
add_executable(mysplit mysplit.c)
add_executable(mystop mystop.c)

add_executable(tsh tsh.c)

file(COPY "driver/" DESTINATION "./")