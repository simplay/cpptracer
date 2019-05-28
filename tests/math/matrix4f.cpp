#include "math/matrix4f.h"
#include <gtest/gtest.h>
#include <iostream>
#include "math/vector4f.h"

TEST(Matrix4f, new_with_floats) {
  Matrix4f mat = Matrix4f(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

  ASSERT_EQ(1, mat.m00);
  ASSERT_EQ(2, mat.m01);
  ASSERT_EQ(3, mat.m02);
  ASSERT_EQ(4, mat.m03);
  ASSERT_EQ(5, mat.m10);
  ASSERT_EQ(6, mat.m11);
  ASSERT_EQ(7, mat.m12);
  ASSERT_EQ(8, mat.m13);
  ASSERT_EQ(9, mat.m20);
  ASSERT_EQ(10, mat.m21);
  ASSERT_EQ(11, mat.m22);
  ASSERT_EQ(12, mat.m23);
  ASSERT_EQ(13, mat.m30);
  ASSERT_EQ(14, mat.m31);
  ASSERT_EQ(15, mat.m32);
  ASSERT_EQ(16, mat.m33);
}

TEST(Matrix4f, mult) {
  Vector4f r1(1, 0, 0, 0);
  Vector4f r2(1, 1, 0, 0);
  Vector4f r3(1, 1, 1, 0);
  Vector4f r4(1, 1, 1, 1);

  Matrix4f mat(r1, r2, r3, r4, true);
  Vector4f v(1, 2, 3, 4);

  auto r = mat.mult(v);
  ASSERT_EQ(1, r->x);
  ASSERT_EQ(3, r->y);
  ASSERT_EQ(6, r->z);
  ASSERT_EQ(10, r->w);

  delete r;
}

TEST(Matrix4f, matrixMult) {
  // clang-format off
  Matrix4f A(
    5, 2, 6, 1,
    0, 6, 2, 0,
    3, 8, 1, 4,
    1, 8, 5, 6
  );

  Matrix4f B(
    7, 5, 8, 0,
    1, 8, 2, 6,
    9, 4, 3, 8,
    5, 3, 7, 9
  );
  // clang-format on

  auto mat = A.mult(B);

  ASSERT_EQ(96, mat->m00);
  ASSERT_EQ(68, mat->m01);
  ASSERT_EQ(69, mat->m02);
  ASSERT_EQ(69, mat->m03);

  ASSERT_EQ(24, mat->m10);
  ASSERT_EQ(56, mat->m11);
  ASSERT_EQ(18, mat->m12);
  ASSERT_EQ(52, mat->m13);

  ASSERT_EQ(58, mat->m20);
  ASSERT_EQ(95, mat->m21);
  ASSERT_EQ(71, mat->m22);
  ASSERT_EQ(92, mat->m23);

  ASSERT_EQ(90, mat->m30);
  ASSERT_EQ(107, mat->m31);
  ASSERT_EQ(81, mat->m32);
  ASSERT_EQ(142, mat->m33);

  delete mat;
}

TEST(Matrix4f, rotX) {
  float v = 1.0 / sqrt(2.0);
  float angle = 3.1415 / 4.0;
  auto m = Matrix4f::rotX(angle);

  float eps = 1e-4;
  // computed via octave
  ASSERT_NEAR(1.0, m->m00, eps);
  ASSERT_NEAR(0.0, m->m01, eps);
  ASSERT_NEAR(0.0, m->m02, eps);
  ASSERT_NEAR(0, m->m03, eps);

  ASSERT_NEAR(0., m->m10, eps);
  ASSERT_NEAR(v, m->m11, eps);
  ASSERT_NEAR(-v, m->m12, eps);
  ASSERT_NEAR(0., m->m13, eps);

  ASSERT_NEAR(0., m->m20, eps);
  ASSERT_NEAR(v, m->m21, eps);
  ASSERT_NEAR(v, m->m22, eps);
  ASSERT_NEAR(0., m->m23, eps);

  ASSERT_NEAR(0., m->m30, eps);
  ASSERT_NEAR(0., m->m31, eps);
  ASSERT_NEAR(0., m->m32, eps);
  ASSERT_NEAR(1., m->m33, eps);

  delete m;
}

TEST(Matrix4f, rotY) {
  float v = 1.0 / sqrt(2.0);
  float angle = 3.1415 / 4.0;
  auto m = Matrix4f::rotY(angle);

  float eps = 1e-4;
  // computed via octave
  ASSERT_NEAR(v, m->m00, eps);
  ASSERT_NEAR(0.0, m->m01, eps);
  ASSERT_NEAR(v, m->m02, eps);
  ASSERT_NEAR(0, m->m03, eps);

  ASSERT_NEAR(0., m->m10, eps);
  ASSERT_NEAR(1, m->m11, eps);
  ASSERT_NEAR(0, m->m12, eps);
  ASSERT_NEAR(0., m->m13, eps);

  ASSERT_NEAR(-v, m->m20, eps);
  ASSERT_NEAR(0, m->m21, eps);
  ASSERT_NEAR(v, m->m22, eps);
  ASSERT_NEAR(0., m->m23, eps);

  ASSERT_NEAR(0., m->m30, eps);
  ASSERT_NEAR(0., m->m31, eps);
  ASSERT_NEAR(0., m->m32, eps);
  ASSERT_NEAR(1., m->m33, eps);

  delete m;
}

TEST(Matrix4f, rotZ) {
  float v = 1.0 / sqrt(2.0);
  float angle = 3.1415 / 4.0;
  auto m = Matrix4f::rotZ(angle);

  float eps = 1e-4;
  // computed via octave
  ASSERT_NEAR(v, m->m00, eps);
  ASSERT_NEAR(-v, m->m01, eps);
  ASSERT_NEAR(0, m->m02, eps);
  ASSERT_NEAR(0, m->m03, eps);

  ASSERT_NEAR(v, m->m10, eps);
  ASSERT_NEAR(v, m->m11, eps);
  ASSERT_NEAR(0, m->m12, eps);
  ASSERT_NEAR(0., m->m13, eps);

  ASSERT_NEAR(0, m->m20, eps);
  ASSERT_NEAR(0, m->m21, eps);
  ASSERT_NEAR(1, m->m22, eps);
  ASSERT_NEAR(0., m->m23, eps);

  ASSERT_NEAR(0., m->m30, eps);
  ASSERT_NEAR(0., m->m31, eps);
  ASSERT_NEAR(0., m->m32, eps);
  ASSERT_NEAR(1., m->m33, eps);

  delete m;
}

TEST(Matrix4f, det) {
  Matrix4f mat(3, 2, -1, 4, 2, 1, 5, 7, 0, 5, 2, -6, -1, 2, 1, 0);
  ASSERT_EQ(-418, mat.det());
}

TEST(Matrix4f, inv) {
  Matrix4f mat(3, 2, -1, 4, 2, 1, 5, 7, 0, 5, 2, -6, -1, 2, 1, 0);

  auto m = mat.inv();

  float eps = 1e-2;
  // computed via octave
  ASSERT_NEAR(0.112440, m->m00, eps);
  ASSERT_NEAR(0.066986, m->m01, eps);
  ASSERT_NEAR(0.153110, m->m02, eps);
  ASSERT_NEAR(-0.528708, m->m03, eps);

  ASSERT_NEAR(0.133971, m->m10, eps);
  ASSERT_NEAR(-0.047847, m->m11, eps);
  ASSERT_NEAR(0.033493, m->m12, eps);
  ASSERT_NEAR(0.306220, m->m13, eps);

  ASSERT_NEAR(-0.155502, m->m20, eps);
  ASSERT_NEAR(0.162679, m->m21, eps);
  ASSERT_NEAR(0.086124, m->m22, eps);
  ASSERT_NEAR(-0.141148, m->m23, eps);

  ASSERT_NEAR(0.059809, m->m30, eps);
  ASSERT_NEAR(0.014354, m->m31, eps);
  ASSERT_NEAR(-0.110048, m->m32, eps);
  ASSERT_NEAR(0.208134, m->m33, eps);

  delete m;
}

TEST(Matrix4f, scale) {
  Matrix4f mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

  mat.scale(0.5);
  ASSERT_EQ(0.5, mat.m00);
  ASSERT_EQ(1, mat.m01);
  ASSERT_EQ(1.5, mat.m02);
  ASSERT_EQ(2, mat.m03);
  ASSERT_EQ(2.5, mat.m10);
  ASSERT_EQ(3, mat.m11);
  ASSERT_EQ(3.5, mat.m12);
  ASSERT_EQ(4, mat.m13);
  ASSERT_EQ(4.5, mat.m20);
  ASSERT_EQ(5, mat.m21);
  ASSERT_EQ(5.5, mat.m22);
  ASSERT_EQ(6, mat.m23);
  ASSERT_EQ(6.5, mat.m30);
  ASSERT_EQ(7, mat.m31);
  ASSERT_EQ(7.5, mat.m32);
  ASSERT_EQ(8, mat.m33);
}

TEST(Matrix4f, transposed) {
  Matrix4f m(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

  auto mat = m.transposed();
  ASSERT_EQ(1, mat->m00);
  ASSERT_EQ(5, mat->m01);
  ASSERT_EQ(9, mat->m02);
  ASSERT_EQ(13, mat->m03);
  ASSERT_EQ(2, mat->m10);
  ASSERT_EQ(6, mat->m11);
  ASSERT_EQ(10, mat->m12);
  ASSERT_EQ(14, mat->m13);
  ASSERT_EQ(3, mat->m20);
  ASSERT_EQ(7, mat->m21);
  ASSERT_EQ(11, mat->m22);
  ASSERT_EQ(15, mat->m23);
  ASSERT_EQ(4, mat->m30);
  ASSERT_EQ(8, mat->m31);
  ASSERT_EQ(12, mat->m32);
  ASSERT_EQ(16, mat->m33);

  delete mat;
}

TEST(Matrix4f, eye) {
  auto m = Matrix4f::eye();

  auto mat = m->transposed();
  ASSERT_EQ(1, mat->m00);
  ASSERT_EQ(0, mat->m01);
  ASSERT_EQ(0, mat->m02);
  ASSERT_EQ(0, mat->m03);
  ASSERT_EQ(0, mat->m10);
  ASSERT_EQ(1, mat->m11);
  ASSERT_EQ(0, mat->m12);
  ASSERT_EQ(0, mat->m13);
  ASSERT_EQ(0, mat->m20);
  ASSERT_EQ(0, mat->m21);
  ASSERT_EQ(1, mat->m22);
  ASSERT_EQ(0, mat->m23);
  ASSERT_EQ(0, mat->m30);
  ASSERT_EQ(0, mat->m31);
  ASSERT_EQ(0, mat->m32);
  ASSERT_EQ(1, mat->m33);

  delete m;
  delete mat;
}
