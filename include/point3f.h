#include "vector4f.h"

#ifndef POINT3_H
#define POINT3_H

/**
 * Float valued point with 3 coordinates.
 */
class Point3f {
    float _x, _y, _z;

	public:

  Point3f();
  Point3f(float, float, float);
  Point3f(Point3f*);
  Point3f(Vector4f*);

  float x();
  float y();
  float z();

  // scale components of this point equally.
  void scale(float factor);

  // Modifies the components of this point.
  void sub(Point3f other);

  // Modifies the components of this point.
  void add(Point3f other);

  // compute the cross product between this and another point.
  Point3f cross(Point3f other);

  /**
   * @return l2-dot product of this point's coordinates.
   */
  float dot();

  // Make length of this vector equal 1 (in l2 norm's sense) but preserve its
  // direction.
  void normalize();

  void debug();
};

#endif
