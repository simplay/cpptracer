#include <gtest/gtest.h>
#include <iostream>
#include "vector4f.h"
#include "point3f.h"

TEST(Vector4f, with_no_args) {
  auto v = new Vector4f();
  ASSERT_EQ(0, v->x);
  ASSERT_EQ(0, v->y);
  ASSERT_EQ(0, v->z);
  ASSERT_EQ(0, v->w);
}

TEST(Vector4f, with_floats) {
  auto v = new Vector4f(1, 2, 3, 4);
  ASSERT_EQ(1, v->x);
  ASSERT_EQ(2, v->y);
  ASSERT_EQ(3, v->z);
  ASSERT_EQ(4, v->w);
}

TEST(Vector4f, create_with_point3f_and_float) {
  auto v = new Vector4f(new Point3f(1, 2, 3), 4);
  ASSERT_EQ(1, v->x);
  ASSERT_EQ(2, v->y);
  ASSERT_EQ(3, v->z);
  ASSERT_EQ(4, v->w);
}

TEST(Vector4f, dot) {
  auto p = new Vector4f(1, -2, 3, 4);
  auto q = new Vector4f(-10, 20, 30, 40);

  // -10 - 40 + 90 + 160
  ASSERT_EQ(200, p->dot(q));
}

TEST(Vector4f, toPoint3f) {
  auto v = new Vector4f(new Point3f(1, 2, 3), 4);
  auto p = v->toPoint3f();
  ASSERT_EQ(1, p->x);
  ASSERT_EQ(2, p->y);
  ASSERT_EQ(3, p->z);
}
