#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "../hitRecord.h"
#include "../ray.h"
#include "intersectable.h"
#include "math/vector3f.h"

/**
 * Axis Aligned Bounding Box (AABB)
 *
 *                           top-right
 *         (min_x, max_y)    (max_x, max_y)
 *               +-----------------+
 *               |                 |
 *               |       AABB      |
 *               |                 |
 *               |                 |
 *               +-----------------+
 *         (min_x, min_y)    (max_x, min_y)
 *         bottom-left
 */
class BoundingBox : public Intersectable {
 private:
  const Vector3f bottomLeft;
  const Vector3f topRight;

 public:
  BoundingBox(const Vector3f& bottomLeft, const Vector3f& topRight);
  HitRecord* intersect(const Ray& ray) const;
};
#endif
