#ifndef RAY_H
#define RAY_H

#include <string>

#include "math/matrix4f.h"
#include "math/vector3f.h"

/**
 * Float valued point with 3 coordinates.
 */
class Ray {
 private:
  float EPSILON = 0.00001;
  Vector3f* perturbatedOrigin(Vector3f* oldOrigin, Vector3f* direction);

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
};
#endif
