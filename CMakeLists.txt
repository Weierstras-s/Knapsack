cmake_minimum_required(VERSION 3.16)
project(Knapsack)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

aux_source_directory(src/adt srcs)
aux_source_directory(src/generator srcs)
aux_source_directory(src/solver srcs)
aux_source_directory(src/utils srcs)

add_executable(Knapsack main.cpp ${srcs})

