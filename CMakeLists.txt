cmake_minimum_required(VERSION 3.31)
project(MedianLib)

set(CMAKE_CXX_STANDARD 20)

add_library(MedianLib STATIC median_filter_algorithms.cpp)

add_subdirectory(tests)
