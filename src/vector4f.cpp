#include "vector4f.h"

Vector4f::Vector4f() {
  _x = 0;
  _y = 0;
  _z = 0;
  _w = 0;
}

Vector4f::Vector4f(float x, float y, float z, float w) {
  _x = x;
  _y = y;
  _z = z;
  _w = w;
}

float Vector4f::x() {
  return _x;
}

float Vector4f::y() {
  return _y;
}

float Vector4f::z() {
  return _z;
}

float Vector4f::w() {
  return _w;
}

float Vector4f::dot(Vector4f other) {
  return _x * other.x() + _y * other.y() + _z * other.z() + _w * other.w();
}
