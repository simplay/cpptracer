#include "point3f.h"
#include "vector4f.h"
#include <cmath>
#include <iostream>

Point3f::Point3f() {
  _x = 0;
  _y = 0;
  _z = 0;
}

Point3f::Point3f(float x, float y, float z) {
  _x = x;
  _y = y;
  _z = z;
}

Point3f::Point3f(Point3f* other) {
  _x = other->x();
  _y = other->y();
  _z = other->z();
}

Point3f::Point3f(Vector4f* other) {
  _x = other->x();
  _y = other->y();
  _z = other->z();
}

float Point3f::x() {
  return _x;
}

float Point3f::y() {
  return _y;
}

float Point3f::z() {
  return _z;
}

void Point3f::scale(float factor) {
  _x *= factor;
  _y *= factor;
  _z *= factor;
}

void Point3f::add(Point3f other) {
  _x += other.x();
  _y += other.y();
  _z += other.z();
}

void Point3f::sub(Point3f other) {
  _x -= other.x();
  _y -= other.y();
  _z -= other.z();
}

void Point3f::negate() {
  _x *= -1.0;
  _y *= -1.0;
  _z *= -1.0;
}

Point3f Point3f::cross(Point3f other) {
  float cx = this->y() * other.z() - this->z() * other.y();
  float cy = this->z() * other.x() - this->x() * other.z();
  float cz = this->x() * other.y() - this->y() * other.x();
  return Point3f(cx, cy, cz);
}

void Point3f::normalize() {
  float scale = this->dot();
  if (scale == 0) return;
  this->scale(1.0 / scale);
}

float Point3f::dot() {
  return _x * _x + _y * _y + _z * _z;
}

float Point3f::dot(Point3f other) {
  return _x * other.x() + _y * other.y() + _z * other.z();
}

void Point3f::debug() {
  std::cout << "(" << _x << ", " << _y << ", " << _z << ")" << std::endl;
}
