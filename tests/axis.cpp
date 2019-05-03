#include "intersectables/axis.h"
#include <gtest/gtest.h>

TEST(Axis, nextLabel) {
  ASSERT_EQ(Axis::Label::Y, Axis::nextLabel(Axis::Label::X));
  ASSERT_EQ(Axis::Label::Z, Axis::nextLabel(Axis::Label::Y));
  ASSERT_EQ(Axis::Label::X, Axis::nextLabel(Axis::Label::Z));
}

TEST(Axis, valueOf) {
  auto v = Vector3f(3, 4, 5);
  ASSERT_EQ(3, Axis::valueOf(Axis::Label::X, v));
  ASSERT_EQ(4, Axis::valueOf(Axis::Label::Y, v));
  ASSERT_EQ(5, Axis::valueOf(Axis::Label::Z, v));
}
