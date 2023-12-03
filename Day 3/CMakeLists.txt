project(AoC_day3)
cmake_minimum_required(VERSION 3.16.3)

add_executable(AoC_day3 Day3.cpp)
# copy the input file to the build directory
configure_file(${CMAKE_SOURCE_DIR}/input.txt ${CMAKE_BINARY_DIR}/input.txt COPYONLY)