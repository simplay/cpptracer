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
    int depth;

    // Image coordinates: used for debugging purposes
    int i;
    int j;

    Ray();
    Ray(Point3f* origin, Point3f* direction);
    Ray(Point3f* origin, Point3f* direction, int i, int j);
    Ray(Point3f* origin, Point3f* direction, int depth);

    // Get point on ray at origin + direction * t
    Point3f* pointAt(float t);
};

#endif
