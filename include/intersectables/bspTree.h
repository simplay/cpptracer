#ifndef BSP_TREE_H
#define BSP_TREE_H

#include "../hitRecord.h"
#include "../ray.h"
#include "boundingBox.h"
#include "intersectable.h"
#include "math/vector3f.h"

#include <vector>

/**
 * An acceleration data-structure that performs a spatial sibdivision via
 * binary space partition trees.
 */
class BspTree : public Intersectable {
 private:
  const Intersectable& intersectable;
  BoundingBox aabb;
  BoundingBox initBoundingBox() { return BoundingBox(Vector3f(0, 0, 0), Vector3f(0, 0, 0)); }

 public:
  BspTree(const Intersectable&);
  HitRecord* intersect(const Ray& ray) const;
  const BoundingBox& getBoundingBox() const;
};
#endif
