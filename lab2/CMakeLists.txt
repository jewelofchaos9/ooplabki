cmake_minimum_required(VERSION 3.16)
project(testik)

add_executable(test main.cpp curve.cpp curve.hpp)
target_link_libraries(test PRIVATE gtest)

#add_executable(test_curve curve.cpp)
#include(FetchContent)
#FetchContent_Declare(
#  googletest
#  GIT_REPOSITORY https://github.com/google/googletest.git
#  GIT_TAG release-1.12.1
#)
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)
#enable_testing()
#target_link_libraries(
#  test_curve
#  GTest::gtest_main
#  gtest
#)
#include(GoogleTest)
#gtest_discover_tests(test_curve)
#
#
#project(curve)
#add_executable(curve main.cpp curve.cpp)
#
