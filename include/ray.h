#include <string>
#include "math/point3f.h"

#ifndef RAY_H
#define RAY_H

/**
 * Float valued point with 3 coordinates.
 */
class Ray {
  public:
    Point3f* origin;
    Point3f* direction;
    float t;

    Ray();
    Ray(Point3f* origin, Point3f* direction, float t);

    // Get point on ray at origin + direction * t
    Point3f* pointAt(float t);
};

#endif
