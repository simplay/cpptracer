#include "math/vector4f.h"
#include <gtest/gtest.h>
#include <iostream>
#include "math/vector3f.h"

TEST(Vector4f, with_no_args) {
  auto v = Vector4f();
  ASSERT_EQ(0, v.x);
  ASSERT_EQ(0, v.y);
  ASSERT_EQ(0, v.z);
  ASSERT_EQ(0, v.w);
}

TEST(Vector4f, with_floats) {
  auto v = Vector4f(1, 2, 3, 4);
  ASSERT_EQ(1, v.x);
  ASSERT_EQ(2, v.y);
  ASSERT_EQ(3, v.z);
  ASSERT_EQ(4, v.w);
}

TEST(Vector4f, create_with_point3f_and_float) {
  auto v = Vector4f(Vector3f(1, 2, 3), 4);
  ASSERT_EQ(1, v.x);
  ASSERT_EQ(2, v.y);
  ASSERT_EQ(3, v.z);
  ASSERT_EQ(4, v.w);
}

TEST(Vector4f, dot) {
  auto p = Vector4f(1, -2, 3, 4);
  auto q = Vector4f(-10, 20, 30, 40);

  // -10 - 40 + 90 + 160
  ASSERT_EQ(200, p.dot(q));
}

TEST(Vector4f, toVector3f) {
  auto v = Vector4f(Vector3f(1, 2, 3), 4);
  auto p = v.toVector3f();
  ASSERT_EQ(1, p->x);
  ASSERT_EQ(2, p->y);
  ASSERT_EQ(3, p->z);
  delete p;
}
