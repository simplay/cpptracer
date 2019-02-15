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

    ~Ray();
    Ray(Point3f* origin, Point3f* direction, bool perturbate = true);
    Ray(Point3f* origin, Point3f* direction, int i, int j, bool perturbate = true);
    Ray(Point3f* origin, Point3f* direction, int depth, bool perturbate = true);

    // Get point on ray at origin + direction * t
    Point3f* pointAt(float t);

    void log() {
      origin->log();
      direction->log();

      printf("(%i, %i, %i)\n", i, j, depth);
    }
};

#endif
