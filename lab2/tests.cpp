#include <gtest/gtest.h>
#include "curve.hpp"

TEST(yFromXTest, BasicAssertions){
  curves::Conchoid conchoid = curves::Conchoid(2,5);
  EXPECT_EQ(conchoid.yFromX(1.3), 9.19426);
  EXPECT_EQ(conchoid.yFromX(2.3), 38.2643);
  EXPECT_EQ(conchoid.yFromX(0.3), 0.829787);
}
