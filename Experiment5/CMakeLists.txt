cmake_minimum_required(VERSION 3.8)
project(CSCPP C)

set(CMAKE_C_STANDARD 99)
add_executable(csim csim.c cachelab.c cachelab.h)
add_executable(test-trans test-trans.c trans.c cachelab.c)
add_executable(tracegen tracegen.c trans.c cachelab.c)

file(COPY "traces" DESTINATION "traces")