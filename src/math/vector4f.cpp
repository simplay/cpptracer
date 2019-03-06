#include "vector4f.h"
#include "vector3f.h"

Vector4f::Vector4f()
  : x(0), y(0), z(0), w(0) {}

Vector4f::Vector4f(float x, float y, float z, float w)
  : x(x), y(y), z(z), w(w) {}

Vector4f::Vector4f(Vector3f* p, float w)
  : x(p->x), y(p->y), z(p->z), w(w) {}

float Vector4f::dot(Vector4f* other) {
  return x * other->x + y * other->y + z * other->z + w * other->w;
}

Vector3f* Vector4f::toVector3f() {
  return new Vector3f(x, y, z);
}
