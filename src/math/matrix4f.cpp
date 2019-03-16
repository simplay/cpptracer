#include "math/matrix4f.h"
#include <iostream>
#include "math/matrix3f.h"
#include "math/vector4f.h"

Matrix4f::Matrix4f()
    : m00(0),
      m01(0),
      m02(0),
      m03(0),
      m10(0),
      m11(0),
      m12(0),
      m13(0),
      m20(0),
      m21(0),
      m22(0),
      m23(0),
      m30(0),
      m31(0),
      m32(0),
      m33(0) {}

Matrix4f::Matrix4f(float m00, float m01, float m02, float m03, float m10, float m11, float m12,
                   float m13, float m20, float m21, float m22, float m23, float m30, float m31,
                   float m32, float m33)
    : m00(m00),
      m01(m01),
      m02(m02),
      m03(m03),
      m10(m10),
      m11(m11),
      m12(m12),
      m13(m13),
      m20(m20),
      m21(m21),
      m22(m22),
      m23(m23),
      m30(m30),
      m31(m31),
      m32(m32),
      m33(m33) {}

Matrix4f::Matrix4f(const Vector4f& v1, const Vector4f& v2, const Vector4f& v3, const Vector4f& v4,
                   bool readRowWise) {
  if (readRowWise) {
    m00 = v1.x;
    m01 = v1.y;
    m02 = v1.z;
    m03 = v1.w;
    m10 = v2.x;
    m11 = v2.y;
    m12 = v2.z;
    m13 = v2.w;
    m20 = v3.x;
    m21 = v3.y;
    m22 = v3.z;
    m23 = v3.w;
    m30 = v4.x;
    m31 = v4.y;
    m32 = v4.z;
    m33 = v4.w;
  } else {
    m00 = v1.x;
    m01 = v2.x;
    m02 = v3.x;
    m03 = v4.x;
    m10 = v1.y;
    m11 = v2.y;
    m12 = v3.y;
    m13 = v4.y;
    m20 = v1.z;
    m21 = v2.z;
    m22 = v3.z;
    m23 = v4.z;
    m30 = v1.w;
    m31 = v2.w;
    m32 = v3.w;
    m33 = v4.w;
  }
}

Vector4f* Matrix4f::mult(const Vector4f& other) {
  Vector4f v1(m00, m01, m02, m03);
  Vector4f v2(m10, m11, m12, m13);
  Vector4f v3(m20, m21, m22, m23);
  Vector4f v4(m30, m31, m32, m33);

  return new Vector4f(v1.dot(other), v2.dot(other), v3.dot(other), v4.dot(other));
}

void Matrix4f::scale(float f) {
  this->m00 *= f;
  this->m01 *= f;
  this->m02 *= f;
  this->m03 *= f;

  this->m10 *= f;
  this->m11 *= f;
  this->m12 *= f;
  this->m13 *= f;

  this->m20 *= f;
  this->m21 *= f;
  this->m22 *= f;
  this->m23 *= f;

  this->m30 *= f;
  this->m31 *= f;
  this->m32 *= f;
  this->m33 *= f;
}

// computed via recursive definition of a determinant
float Matrix4f::det() {
  float r10 = m00 * m11 * m22 * m33 + m00 * m12 * m23 * m31 + m00 * m13 * m21 * m32;
  float r11 = m00 * m13 * m22 * m31 + m00 * m12 * m21 * m33 + m00 * m11 * m23 * m32;

  float r21 = m01 * m10 * m22 * m33 + m02 * m10 * m23 * m31 + m03 * m10 * m21 * m32;
  float r22 = m03 * m10 * m22 * m31 + m02 * m10 * m21 * m33 + m01 * m10 * m23 * m32;

  float r31 = m01 * m12 * m20 * m33 + m02 * m13 * m20 * m31 + m03 * m11 * m20 * m32;
  float r32 = m03 * m12 * m20 * m31 + m02 * m11 * m20 * m33 + m01 * m13 * m20 * m32;

  float r41 = m01 * m12 * m23 * m30 + m02 * m13 * m21 * m30 + m03 * m11 * m22 * m30;
  float r42 = m03 * m12 * m21 * m30 + m02 * m11 * m23 * m30 + m01 * m13 * m22 * m30;

  return r10 - r11 - r21 + r22 + r31 - r32 - r41 + r42;
}

Matrix4f* Matrix4f::transposed() {
  // clang-format off
  return new Matrix4f(m00, m10, m20, m30,
                      m01, m11, m21, m31,
                      m02, m12, m22, m32,
                      m03, m13, m23, m33);
  // clang-format on
}

Matrix4f* Matrix4f::inv() {
  Matrix3f a00(m11, m12, m13, m21, m22, m23, m31, m32, m33);

  Matrix3f a01(m10, m12, m13, m20, m22, m23, m30, m32, m33);

  Matrix3f a02(m10, m11, m13, m20, m21, m23, m30, m31, m33);

  Matrix3f a03(m10, m11, m12, m20, m21, m22, m30, m31, m32);

  Matrix3f a10(m01, m02, m03, m21, m22, m23, m31, m32, m33);

  Matrix3f a11(m00, m02, m03, m20, m22, m23, m30, m32, m33);

  Matrix3f a12(m00, m01, m03, m20, m21, m23, m30, m31, m33);

  Matrix3f a13(m00, m01, m02, m20, m21, m22, m30, m31, m32);

  Matrix3f a20(m01, m02, m03, m11, m12, m13, m31, m32, m33);

  Matrix3f a21(m00, m02, m03, m10, m12, m13, m30, m32, m33);

  Matrix3f a22(m00, m01, m03, m10, m11, m13, m30, m31, m33);

  Matrix3f a23(m00, m01, m02, m10, m11, m12, m30, m31, m32);

  Matrix3f a30(m01, m02, m03, m11, m12, m13, m21, m22, m23);

  Matrix3f a31(m00, m02, m03, m10, m12, m13, m20, m22, m23);

  Matrix3f a32(m00, m01, m03, m10, m11, m13, m20, m21, m23);

  Matrix3f a33(m00, m01, m02, m10, m11, m12, m20, m21, m22);

  // clang-format off
  // a_ij = (-1)^(i + j) det(a_ji)
  auto mat = new Matrix4f( a00.det(), -a10.det(),  a20.det(), -a30.det(),
                          -a01.det(),  a11.det(), -a21.det(),  a31.det(),
                           a02.det(), -a12.det(),  a22.det(), -a32.det(),
                          -a03.det(),  a13.det(), -a23.det(),  a33.det());
  // clang-format on

  mat->scale(1.0 / det());

  return mat;
}
