#include <gtest/gtest.h>

#include "point3f.h"

TEST(Point3f, create_with_arguments) {
  Point3f d = Point3f(1, 2, 3);
  ASSERT_EQ(1, d.x());
  ASSERT_EQ(2, d.y());
  ASSERT_EQ(3, d.z());
}

TEST(Point3f, new_without_arguments) {
  Point3f d = Point3f();
  ASSERT_EQ(0, d.x());
  ASSERT_EQ(0, d.y());
  ASSERT_EQ(0, d.z());
}

TEST(Point3f, dot) {
  Point3f d = Point3f(0, 3, 4);
  ASSERT_EQ(5, d.dot());
}