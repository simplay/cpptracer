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

