#include "matrix3f.h"

Matrix3f::Matrix3f()
  : m00(0), m01(0), m02(0),
    m10(0), m11(0), m12(0),
    m20(0), m21(0), m22(0) {}

Matrix3f::Matrix3f(
    float m00, float m01, float m02,
    float m10, float m11, float m12,
    float m20, float m21, float m22
): m00(m00), m01(m01), m02(m02),
   m10(m10), m11(m11), m12(m12),
   m20(m20), m21(m21), m22(m22) {}

Point3f* Matrix3f::mult(Point3f* other) {
  return new Point3f(
    m00 * other->x + m01 * other->y + m02 * other->z,
    m10 * other->x + m11 * other->y + m12 * other->z,
    m20 * other->x + m21 * other->y + m22 * other->z
  );
}

float Matrix3f::det() {
  float a = m00*(m11 * m22 - m12 * m21);
  float b = m01*(m10 * m22 - m12 * m20);
  float c = m02*(m10 * m21 - m11 * m20);
  return a - b + c;
}

void Matrix3f::scale(float f) {
  m00 *= f; m01 *= f; m02 *= f;
  m10 *= f; m11 *= f; m12 *= f;
  m20 *= f; m21 *= f; m22 *= f;
}

Matrix3f* Matrix3f::inv() {
  // adjugate matrix: see http://mathworld.wolfram.com/MatrixInverse.html
  Matrix3f* mat = new Matrix3f(
    m11 * m22 - m12 * m21, m02 * m21 - m01 * m22, m01 * m12 - m02 * m11,
    m12 * m20 - m10 * m22, m00 * m22 - m02 * m20, m02 * m10 - m00 * m12,
    m10 * m21 - m11 * m20, m01 * m20 - m00 * m21, m00 * m11 - m01 * m10
  );

  mat->scale(1.0 / det());

  return mat;
}
