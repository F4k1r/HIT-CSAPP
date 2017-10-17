cmake_minimum_required(VERSION 3.8)
project(CSCPP C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-O -Wall -m32")

add_executable(btest btest.c bits.c decl.c tests.c btest.h bits.h)

add_executable(fshow fshow.c)

add_executable(ishow ishow.c)

# Forces a recompile. Used by the driver program.
add_executable(rbtest bits.c btest.c decl.c tests.c)
