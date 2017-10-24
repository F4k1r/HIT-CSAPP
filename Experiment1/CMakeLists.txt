cmake_minimum_required(VERSION 3.8)
project(CSCPP C)

set(CMAKE_C_STANDARD 99)

add_executable(hellowin hellowin.c)
add_executable(hellolinux hellolinux.c)
add_executable(datatype datatype.c)
add_executable(showbytes showbytes.c)
add_executable(sysinfo sysinfo.c)
add_executable(sum sum.c)
add_executable(float float.c)