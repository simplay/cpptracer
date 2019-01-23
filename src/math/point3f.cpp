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

void Point3f::add(Point3f* other) {
  x += other->x;
  y += other->y;
  z += other->z;
}

void Point3f::sub(Point3f* other) {
  x -= other->x;
  y -= other->y;
  z -= other->z;
}

void Point3f::negate() {
  x *= -1.0;
  y *= -1.0;
  z *= -1.0;
}

Point3f* Point3f::cross(Point3f* other) {
  float cx = this->y * other->z - this->z * other->y;
  float cy = this->z * other->x - this->x * other->z;
  float cz = this->x * other->y - this->y * other->x;
  return new Point3f(cx, cy, cz);
}

void Point3f::normalize() {
  float scale = sqrt(this->dot());
  if (scale == 0) return;
  this->scale(1.0 / scale);
}

float Point3f::dot() {
  return x * x + y * y + z * z;
}

float Point3f::dot(Point3f* other) {
  return x * other->x + y * other->y + z * other->z;
}
