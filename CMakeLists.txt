cmake_minimum_required(VERSION 2.6)

project(peach)

set(
    CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall"
)

add_subdirectory(src/)
add_subdirectory(include/)
