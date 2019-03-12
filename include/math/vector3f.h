#ifndef VECTOR3F_H
#define VECTOR3F_H

#include <stdio.h>
#include "vector4f.h"

/**
 * Float valued point with 3 coordinates.
 */
class Vector3f {
 public:
  float x;
  float y;
  float z;

  Vector3f();
  Vector3f(float, float, float);
  Vector3f(const Vector3f&);
  Vector3f(const Vector4f&);

  static Vector3f* incidentDirection(const Vector3f& v) {
    Vector3f* wIn = new Vector3f(v);
    wIn->negate();
    wIn->normalize();
    return wIn;
  }

  // scale components of this point equally.
  void scale(float factor);

  // Modifies the components of this point.
  void sub(const Vector3f& other);

  // Modifies the components of this point.
  void add(const Vector3f& other);

  void negate();

  void abs();

  // compute the cross product between this and another point.
  Vector3f* cross(const Vector3f& other);

  /**
   * @return l2-dot product of this point's coordinates.
   */
  float dot() const;

  float dot(const Vector3f& other) const;

  float norm() const;

  // Make length of this vector equal 1 (in l2 norm's sense) but preserve its
  // direction.
  void normalize();

  // Overwrites this vector's components by a first scaled and then shifted
  // vector. In other words, it overwrites this vector by scale * base +
  // other
  Vector3f* scaleAdd(float scale, const Vector3f& base, const Vector3f& other);

  // First scales this vector's component and then adds another vector to it.
  Vector3f* scaleAdd(float scale, const Vector3f& other);

  // reflect the inverse direction of this vector off from a given normal
  // reflected := v + 2 * dot(v, normal) * normal
  Vector3f* invReflected(const Vector3f&);

  void log() const { printf("(%f, %f, %f)\n", x, y, z); }
};
#endif
