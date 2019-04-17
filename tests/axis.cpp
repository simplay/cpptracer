#include "intersectables/axis.h"
#include <gtest/gtest.h>

TEST(Axis, nextLabel) {
  ASSERT_EQ(Axis::Label::Y, Axis::nextLabel(Axis::Label::X));
  ASSERT_EQ(Axis::Label::Z, Axis::nextLabel(Axis::Label::Y));
  ASSERT_EQ(Axis::Label::X, Axis::nextLabel(Axis::Label::Z));
}

TEST(Axis, valueOf) {
  auto expectedX = Axis::valueOf(Axis::Label::X);
  ASSERT_EQ(1, expectedX.x);
  ASSERT_EQ(0, expectedX.y);
  ASSERT_EQ(0, expectedX.z);

  auto expectedY = Axis::valueOf(Axis::Label::Y);
  ASSERT_EQ(0, expectedY.x);
  ASSERT_EQ(1, expectedY.y);
  ASSERT_EQ(0, expectedY.z);

  auto expectedZ = Axis::valueOf(Axis::Label::Z);
  ASSERT_EQ(0, expectedZ.x);
  ASSERT_EQ(0, expectedZ.y);
  ASSERT_EQ(1, expectedZ.z);
}
