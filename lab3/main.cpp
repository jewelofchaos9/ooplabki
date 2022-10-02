#include <iostream>
#include "binary.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;
int main(){
  binary::Binary a = binary::Binary();
  binary::Binary b = binary::Binary("00011010");
  binary::Binary c = binary::Binary("10011110");

  std::cout << c + b;
  std::cout << (c+b).fromBinary();

  testing::InitGoogleTest();
  RUN_ALL_TESTS();
  return 0;
}
