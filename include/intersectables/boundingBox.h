#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <utility>
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
  BoundingBox& operator=(const BoundingBox& newBB) {
    // This is a hack used to update certain const members whenever we put new
    // members in IntersectableList.
    *(Vector3f*)&bottomLeft = Vector3f(newBB.getBottomLeft());
    *(Vector3f*)&topRight = Vector3f(newBB.getTopRight());
    return *this;
  }

  BoundingBox(const Vector3f& bottomLeft, const Vector3f& topRight);
  HitRecord* intersect(const Ray& ray) const;
  const BoundingBox& getBoundingBox() const;

  const Vector3f& getBottomLeft() const { return bottomLeft; }

  const Vector3f& getTopRight() const { return topRight; }

  BoundingBox transform(Matrix4f& transformation) const;
  void expand(const Intersectable*);
};
#endif
