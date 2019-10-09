cmake_minimum_required(VERSION 3.14)
project(Algorithms-and-Data-Structures)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.cpp)

include_directories(Practicum_1_1_lib)
add_subdirectory(Practicum_1_1_lib)

add_subdirectory(Google_tests)
