#include "matrix3f.h"

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
