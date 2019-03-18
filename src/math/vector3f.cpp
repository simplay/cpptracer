#include "math/vector3f.h"
#include <cmath>
#include <iostream>
#include "math/vector4f.h"

Vector3f::Vector3f() : x(0), y(0), z(0) {}

Vector3f::Vector3f(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3f::Vector3f(const Vector3f& other) {
  x = other.x;
  y = other.y;
  z = other.z;
}

Vector3f::Vector3f(const Vector4f& other) {
  x = other.x;
  y = other.y;
  z = other.z;
}

void Vector3f::scale(float factor) {
  x *= factor;
  y *= factor;
  z *= factor;
}

void Vector3f::add(const Vector3f& other) {
  x += other.x;
  y += other.y;
  z += other.z;
}

void Vector3f::sub(const Vector3f& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
}

void Vector3f::negate() {
  x *= -1.0;
  y *= -1.0;
  z *= -1.0;
}

void Vector3f::abs() {
  x = std::abs(x);
  y = std::abs(y);
  z = std::abs(z);
}

Vector3f* Vector3f::cross(const Vector3f& other) {
  float cx = y * other.z - z * other.y;
  float cy = z * other.x - x * other.z;
  float cz = x * other.y - y * other.x;
  return new Vector3f(cx, cy, cz);
}

float Vector3f::norm() const { return sqrt(this->dot()); }

void Vector3f::normalize() {
  float scale = norm();
  if (scale == 0)
    return;
  this->scale(1.0 / scale);
}

float Vector3f::dot() const { return x * x + y * y + z * z; }

float Vector3f::dot(const Vector3f& other) const { return x * other.x + y * other.y + z * other.z; }

Vector3f* Vector3f::scaleAdd(float scale, const Vector3f& base, const Vector3f& other) {
  x = scale * base.x + other.x;
  y = scale * base.y + other.y;
  z = scale * base.z + other.z;

  return this;
}

Vector3f* Vector3f::scaleAdd(float scale, const Vector3f& other) {
  x = scale * x + other.x;
  y = scale * y + other.y;
  z = scale * z + other.z;

  return this;
}

Vector3f* Vector3f::invReflected(const Vector3f& normal) {
  float cosThetaI = normal.dot(*this);

  Vector3f* reflectedDir = new Vector3f();
  Vector3f wInCopy(*this);

  // inverse direction
  wInCopy.negate();

  reflectedDir->scaleAdd(2.0 * cosThetaI, normal, wInCopy);
  return reflectedDir;
}
