#include <gtest/gtest.h>
#include <iostream>
#include "math/matrix3f.h"
#include "math/point3f.h"

TEST(Matrix3f, mult) {
  Matrix3f* mat = new Matrix3f(
    1, 2, 3,
    4, 5, 6,
    7, 8, 9);

  Point3f* v = new Point3f(1, 10, 100);
  Point3f* r = mat->mult(v);
  ASSERT_EQ(321, r->x);
  ASSERT_EQ(654, r->y);
  ASSERT_EQ(987, r->z);
}

TEST(Matrix3f, det) {
  Matrix3f* mat = new Matrix3f(
      6, 1, 1,
      4, -2, 5,
      2, 8, 7);

  ASSERT_EQ(-306, mat->det());
}

TEST(Matrix3f, inv) {
  Matrix3f* mat = new Matrix3f(
      -24, 18, 5,
      20, -15, -4,
      -5, 4, 1);

  Matrix3f* m = mat->inv();

  ASSERT_EQ(1, m->m00);
  ASSERT_EQ(2, m->m01);
  ASSERT_EQ(3, m->m02);

  ASSERT_EQ(0, m->m10);
  ASSERT_EQ(1, m->m11);
  ASSERT_EQ(4, m->m12);

  ASSERT_EQ(5, m->m20);
  ASSERT_EQ(6, m->m21);
  ASSERT_EQ(0, m->m22);
}

TEST(Matrix3f, scale) {
  Matrix3f* mat = new Matrix3f(
    1, 2, 3,
    4, 5, 6,
    7, 8, 9);

  mat->scale(10);

  ASSERT_EQ(10, mat->m00);
  ASSERT_EQ(20, mat->m01);
  ASSERT_EQ(30, mat->m02);

  ASSERT_EQ(40, mat->m10);
  ASSERT_EQ(50, mat->m11);
  ASSERT_EQ(60, mat->m12);

  ASSERT_EQ(70, mat->m20);
  ASSERT_EQ(80, mat->m21);
  ASSERT_EQ(90, mat->m22);
}
