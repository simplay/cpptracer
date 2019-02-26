#include <iostream>
#include "matrix4f.h"
#include "vector4f.h"

Matrix4f::Matrix4f():
  m00(0), m01(0), m02(0), m03(0),
  m10(0), m11(0), m12(0), m13(0),
  m20(0), m21(0), m22(0), m23(0),
  m30(0), m31(0), m32(0), m33(0) {}


  Matrix4f::Matrix4f(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33
  ):
    m00(m00), m01(m01), m02(m02), m03(m03),
    m10(m10), m11(m11), m12(m12), m13(m13),
    m20(m20), m21(m21), m22(m22), m23(m23),
    m30(m30), m31(m31), m32(m32), m33(m33) {}


Matrix4f::Matrix4f(Vector4f* v1, Vector4f* v2, Vector4f* v3, Vector4f* v4, bool readRowWise) {
  if (readRowWise) {
    m00 = v1->x; m01 = v1->y; m02 = v1->z; m03 = v1->w;
    m10 = v2->x; m11 = v2->y; m12 = v2->z; m13 = v2->w;
    m20 = v3->x; m21 = v3->y; m22 = v3->z; m23 = v3->w;
    m30 = v4->x; m31 = v4->y; m32 = v4->z; m33 = v4->w;
  } else {
    m00 = v1->x; m01 = v2->x; m02 = v3->x; m03 = v4->x;
    m10 = v1->y; m11 = v2->y; m12 = v3->y; m13 = v4->y;
    m20 = v1->z; m21 = v2->z; m22 = v3->z; m23 = v4->z;
    m30 = v1->w; m31 = v2->w; m32 = v3->w; m33 = v4->w;
  }
}

Vector4f* Matrix4f::mult(Vector4f* other) {
  Vector4f v1 (m00, m01, m02, m03);
  Vector4f v2 (m10, m11, m12, m13);
  Vector4f v3 (m20, m21, m22, m23);
  Vector4f v4 (m30, m31, m32, m33);

  Vector4f* v = new Vector4f(
    v1.dot(other),
    v2.dot(other),
    v3.dot(other),
    v4.dot(other)
  );
  return v;
}
