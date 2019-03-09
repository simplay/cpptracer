#include <gtest/gtest.h>
#include <iostream>
#include "math/matrix3f.h"
#include "math/vector3f.h"

TEST(Matrix3f, mult) {
  Matrix3f mat(
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
  );

  Vector3f v(1, 10, 100);
  Vector3f r = mat.mult(&v);
  ASSERT_EQ(321, r.x);
  ASSERT_EQ(654, r.y);
  ASSERT_EQ(987, r.z);
}

TEST(Matrix3f, det) {
  Matrix3f mat = Matrix3f(
    6, 1, 1,
    4, -2, 5,
    2, 8, 7
  );

  ASSERT_EQ(-306, mat.det());
}

TEST(Matrix3f, inv) {
  Matrix3f mat(
    -24, 18, 5,
    20, -15, -4,
    -5, 4, 1
  );

  auto m = mat.inv();

  ASSERT_EQ(1, m->m00);
  ASSERT_EQ(2, m->m01);
  ASSERT_EQ(3, m->m02);

  ASSERT_EQ(0, m->m10);
  ASSERT_EQ(1, m->m11);
  ASSERT_EQ(4, m->m12);

  ASSERT_EQ(5, m->m20);
  ASSERT_EQ(6, m->m21);
  ASSERT_EQ(0, m->m22);

  delete m;
}

// Data was produced via octave
//
// m =
//
// 0.01022   0.13142  -0.21362
// -0.05683  -0.05683   0.42147
// 0.00000   0.45682  -1.00000
//
// octave:2> inverse(m)
// ans =
//
// 41.0024  -10.2215  -13.0657
// 17.1683    3.0884   -2.3658
// 7.8429    1.4109   -2.0808
TEST(Matrix3f, inv2) {

  Matrix3f mat(
    0.01022, 0.13142, -0.21362,
    -0.05683, -0.05683, 0.42147,
    0.00000, 0.45682, -1.00000
  );

  auto m = mat.inv();

  float eps = 1e-2;
  ASSERT_NEAR(41.0024, m->m00, eps);
  ASSERT_NEAR(-10.2215, m->m01, eps);
  ASSERT_NEAR(-13.0657, m->m02, eps);

  ASSERT_NEAR(17.1683, m->m10, eps);
  ASSERT_NEAR(3.0884, m->m11, eps);
  ASSERT_NEAR(-2.3658, m->m12, eps);

  ASSERT_NEAR(7.8429, m->m20, eps);
  ASSERT_NEAR(1.4109, m->m21, eps);
  ASSERT_NEAR(-2.0808, m->m22, eps);

  delete m;
}

TEST(Matrix3f, scale) {
  Matrix3f mat(
    1, 2, 3,
    4, 5, 6,
    7, 8, 9
  );

  mat.scale(10);

  ASSERT_EQ(10, mat.m00);
  ASSERT_EQ(20, mat.m01);
  ASSERT_EQ(30, mat.m02);

  ASSERT_EQ(40, mat.m10);
  ASSERT_EQ(50, mat.m11);
  ASSERT_EQ(60, mat.m12);

  ASSERT_EQ(70, mat.m20);
  ASSERT_EQ(80, mat.m21);
  ASSERT_EQ(90, mat.m22);
}
