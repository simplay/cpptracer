#include <stdio.h>
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
  Matrix4f(Vector4f* v1, Vector4f* v2, Vector4f* v3, Vector4f* v4, bool rowWise);
  Matrix4f(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33
  );

  Vector4f* mult(Vector4f* other);

  void log() {
    printf("%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
        m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
  }
};

#endif
