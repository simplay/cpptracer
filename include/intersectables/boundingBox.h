#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "../hitRecord.h"
#include "../ray.h"
#include "intersectable.h"
#include "math/vector3f.h"

#include <vector>

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
  BoundingBox static buildFromVectors(const std::vector<Vector3f>& vectors);

  BoundingBox(const Vector3f& bottomLeft, const Vector3f& topRight);
  HitRecord* intersect(const Ray& ray) const;
  BoundingBox getBoundingBox() const;

  const Vector3f& getBottomLeft() const { return bottomLeft; }

  const Vector3f& getTopRight() const { return topRight; }
};
#endif
