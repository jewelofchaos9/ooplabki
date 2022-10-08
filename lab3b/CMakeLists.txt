cmake_minimum_required(VERSION 3.16)

project(testik)

add_executable(test main.cpp binary.cpp binary.hpp)

target_link_libraries(test PRIVATE gtest)
