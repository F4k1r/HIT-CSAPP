cmake_minimum_required(VERSION 3.8)
project(CSCPP C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-Wall -O2 -m32")

add_executable(mdriver mdriver.c fsecs.c memlib.c clock.c fcyc.c ftimer.c mm.c config.h)
add_executable(mdriver-im mdriver.c fsecs.c memlib.c clock.c fcyc.c ftimer.c mm-implicit.c config.h)

file(COPY "traces" DESTINATION "./")