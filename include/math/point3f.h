#include <stdio.h>
#include "vector4f.h"

#ifndef POINT3_H
#define POINT3_H

/**
 * Float valued point with 3 coordinates.
 */
class Point3f {
	public:
    float x;
    float y;
    float z;

    Point3f();
    Point3f(float, float, float);
    Point3f(Point3f*);
    Point3f(Vector4f*);

    static Point3f* incidentDirection(Point3f* v) {
      Point3f* wIn = new Point3f(v);
      wIn->negate();
      wIn->normalize();
      return wIn;
    }

    // scale components of this point equally.
    void scale(float factor);

    // Modifies the components of this point.
    void sub(const Point3f* other);

    // Modifies the components of this point.
    void add(const Point3f* other);

    void negate();

    void abs();

    // compute the cross product between this and another point.
    Point3f* cross(const Point3f* other);

    /**
     * @return l2-dot product of this point's coordinates.
     */
    float dot() const;

    float dot(const Point3f* other) const;

    float norm() const;

    // Make length of this vector equal 1 (in l2 norm's sense) but preserve its
    // direction.
    void normalize();

    // overwrite this by scale * base + other
    Point3f* scaleAdd(float scale, Point3f* base, Point3f* other);

    Point3f* scaleAdd(float scale, Point3f* other);

    // reflect the inverse direction of this vector off from a given normal
    // reflected := v + 2 * dot(v, normal) * normal
    Point3f* invReflected(Point3f*);

    void log() {
      printf("(%f, %f, %f)\n", x, y, z);
    }
};

#endif
