#include "vector4f.h"

#ifndef MATRIX4F_H
#define MATRIX4F_H

class Matrix4f {
  public:

  float m00, m01, m02, m03;
  float m10, m11, m12, m13;
  float m20, m21, m22, m23;
  float m30, m31, m32, m33;

  Matrix4f();
  Matrix4f(Vector4f* row1, Vector4f* row2, Vector4f* row3, Vector4f* row4);

  Vector4f* mult(Vector4f& other);
};

#endif
