#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <cmath>
#include "vector4f.h"

class Matrix4f {
 public:
  float m00, m01, m02, m03;
  float m10, m11, m12, m13;
  float m20, m21, m22, m23;
  float m30, m31, m32, m33;

  Matrix4f();
  Matrix4f(const Vector4f& v1, const Vector4f& v2, const Vector4f& v3, const Vector4f& v4,
           bool rowWise);
  Matrix4f(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13,
           float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33);

  static Matrix4f* eye() {
    // clang-format off
    return new Matrix4f(
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    );
    // clang-format on
  }

  /**
   * @param angle value between 0 and 2*pi
   * @return homogeneous transformation matrix
   **/
  static Matrix4f* rotX(float angle) {
    // clang-format off
    return new Matrix4f(
      1, 0, 0, 0,
      0, cos(angle), -sin(angle), 0,
      0, sin(angle),  cos(angle), 0,
      0, 0,           0,          1
    );
    // clang-format on
  }

  /**
   * @param angle value between 0 and 2*pi
   * @return homogeneous transformation matrix
   **/
  static Matrix4f* rotY(float angle) {
    // clang-format off
    return new Matrix4f(
      cos(angle), 0, sin(angle), 0,
      0,          1, 0,          0,
     -sin(angle), 0, cos(angle), 0,
      0,          0, 0,          1
    );
    // clang-format on
  }

  /**
   * @param angle value between 0 and 2*pi
   * @return homogeneous transformation matrix
   **/
  static Matrix4f* rotZ(float angle) {
    // clang-format off
    return new Matrix4f(
      cos(angle), -sin(angle), 0, 0,
      sin(angle),  cos(angle), 0, 0,
      0,           0,          1, 0,
      0,           0,          0, 1
    );
    // clang-format on
  }

  Matrix4f* mult(const Matrix4f& other);
  Vector4f* mult(const Vector4f& other);
  void scale(float f);

  Matrix4f* inv();
  float det();

  Matrix4f* transposed();
};
#endif
