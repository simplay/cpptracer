#include <string>
#include "math/matrix4f.h"
#include "math/vector3f.h"

#ifndef RAY_H
#define RAY_H

/**
 * Float valued point with 3 coordinates.
 */
class Ray {
 private:
  float EPSILON = 0.00001;

 public:
  Vector3f* origin;
  Vector3f* direction;
  int depth;

  // Image coordinates: used for debugging purposes
  int i;
  int j;

  ~Ray();
  Ray(Vector3f* origin, Vector3f* direction, bool perturbate = true);
  Ray(Vector3f* origin, Vector3f* direction, int i, int j, bool perturbate = true);
  Ray(Vector3f* origin, Vector3f* direction, int depth, bool perturbate = true);

  // Get point on ray at origin + direction * t
  Vector3f* pointAt(float t) const;

  Ray* transform(Matrix4f*) const;

  void log() {
    origin->log();
    direction->log();

    printf("(%i, %i, %i)\n", i, j, depth);
  }
};

#endif
