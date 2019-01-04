#include "point3f.h"
#include <cmath>

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

float Point3f::x() {
  return _x;
}

float Point3f::y() {
  return _y;
}

float Point3f::z() {
  return _z;
}

float Point3f::dot() {
  return sqrtf(_x * _x + _y * _y + _z * _z);
}
