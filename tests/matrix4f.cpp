#include <gtest/gtest.h>
#include "matrix4f.h"
#include "vector4f.h"
#include <iostream>

TEST(Matrix4f, mult) {
  Vector4f* r1 = new Vector4f(1, 0, 0, 0);
  Vector4f* r2 = new Vector4f(1, 1, 0, 0);
  Vector4f* r3 = new Vector4f(1, 1, 1, 0);
  Vector4f* r4 = new Vector4f(1, 1, 1, 1);

  Matrix4f* mat = new Matrix4f(r1, r2, r3, r4);
  Vector4f* v = new Vector4f(1, 2, 3, 4);

  Vector4f* r = mat->mult(v);
  ASSERT_EQ(1, r->x);
  ASSERT_EQ(3, r->y);
  ASSERT_EQ(6, r->z);
  ASSERT_EQ(10, r->w);
}
