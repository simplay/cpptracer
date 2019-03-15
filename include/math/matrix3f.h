#ifndef MATRIX3F_H
#define MATRIX3F_H

#include "vector3f.h"

class Matrix3f {
 public:
  float m00, m01, m02;
  float m10, m11, m12;
  float m20, m21, m22;

  Matrix3f();
  Matrix3f(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21,
           float m22);

  Vector3f* mult(const Vector3f& other);
  float det();
  void scale(float);
  Matrix3f* inv();
};
#endif
