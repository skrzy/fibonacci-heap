cmake_minimum_required(VERSION 3.8)
project(fibonacci_heap)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp fibonacci_heap.h fibonacci_heap_algorithm.h dijkstra.h fibonacci_degree_thresholds.h)
add_executable(fibonacci_heap ${SOURCE_FILES})