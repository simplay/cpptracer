#include <gtest/gtest.h>
#include <iostream>
#include "math/matrix4f.h"
#include "math/vector4f.h"

TEST(Matrix4f, new_with_floats) {
  Matrix4f* mat = new Matrix4f(
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 16
  );
  ASSERT_EQ(1, mat->m00);
  ASSERT_EQ(2, mat->m01);
  ASSERT_EQ(3, mat->m02);
  ASSERT_EQ(4, mat->m03);
  ASSERT_EQ(5, mat->m10);
  ASSERT_EQ(6, mat->m11);
  ASSERT_EQ(7, mat->m12);
  ASSERT_EQ(8, mat->m13);
  ASSERT_EQ(9, mat->m20);
  ASSERT_EQ(10, mat->m21);
  ASSERT_EQ(11, mat->m22);
  ASSERT_EQ(12, mat->m23);
  ASSERT_EQ(13, mat->m30);
  ASSERT_EQ(14, mat->m31);
  ASSERT_EQ(15, mat->m32);
  ASSERT_EQ(16, mat->m33);
}

TEST(Matrix4f, mult) {
  Vector4f* r1 = new Vector4f(1, 0, 0, 0);
  Vector4f* r2 = new Vector4f(1, 1, 0, 0);
  Vector4f* r3 = new Vector4f(1, 1, 1, 0);
  Vector4f* r4 = new Vector4f(1, 1, 1, 1);

  Matrix4f* mat = new Matrix4f(r1, r2, r3, r4, true);
  Vector4f* v = new Vector4f(1, 2, 3, 4);

  Vector4f* r = mat->mult(v);
  ASSERT_EQ(1, r->x);
  ASSERT_EQ(3, r->y);
  ASSERT_EQ(6, r->z);
  ASSERT_EQ(10, r->w);
}

TEST(Matrix4f, det) {
  Matrix4f* mat = new Matrix4f(
    3, 2, -1, 4,
    2, 1, 5, 7,
    0, 5, 2, -6,
    -1, 2, 1, 0
  );
  ASSERT_EQ(-418, mat->det());
}
