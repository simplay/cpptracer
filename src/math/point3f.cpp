#include <cmath>
#include <iostream>
#include "point3f.h"
#include "vector4f.h"

Point3f::Point3f() : x(0), y(0), z(0) {}

Point3f::Point3f(float x, float y, float z)
  : x(x), y(y), z(z) {}

Point3f::Point3f(Point3f* other) {
  x = other->x;
  y = other->y;
  z = other->z;
}

Point3f::Point3f(Vector4f* other) {
  x = other->x;
  y = other->y;
  z = other->z;
}

void Point3f::scale(float factor) {
  x *= factor;
  y *= factor;
  z *= factor;
}

void Point3f::add(const Point3f* other) {
  x += other->x;
  y += other->y;
  z += other->z;
}

void Point3f::sub(const Point3f* other) {
  x -= other->x;
  y -= other->y;
  z -= other->z;
}

void Point3f::negate() {
  x *= -1.0;
  y *= -1.0;
  z *= -1.0;
}

void Point3f::abs() {
  x = std::abs(x);
  y = std::abs(y);
  z = std::abs(z);
}

Point3f* Point3f::cross(const Point3f* other) {
  float cx = this->y * other->z - this->z * other->y;
  float cy = this->z * other->x - this->x * other->z;
  float cz = this->x * other->y - this->y * other->x;
  return new Point3f(cx, cy, cz);
}

float Point3f::norm() const {
  return sqrt(this->dot());
}

void Point3f::normalize() {
  float scale = norm();
  if (scale == 0) return;
  this->scale(1.0 / scale);
}

float Point3f::dot() const {
  return x * x + y * y + z * z;
}

float Point3f::dot(const Point3f* other) const {
  return x * other->x + y * other->y + z * other->z;
}

Point3f* Point3f::scaleAdd(float scale, Point3f* base, Point3f* other) {
  x = scale * base->x + other->x;
  y = scale * base->y + other->y;
  z = scale * base->z + other->z;

  return this;
}

Point3f* Point3f::scaleAdd(float scale, Point3f* other) {
  x = scale * x + other->x;
  y = scale * y + other->y;
  z = scale * z + other->z;

  return this;
}

Point3f* Point3f::invReflected(Point3f* normal) {
  float cosThetaI = normal->dot(this);

  Point3f* reflectedDir = new Point3f();
  Point3f wInCopy(this);

  // inverse direction
  wInCopy.negate();

  reflectedDir->scaleAdd(2.0 * cosThetaI, normal, &wInCopy);
  return reflectedDir;
}
