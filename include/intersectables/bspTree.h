#ifndef BSP_TREE_H
#define BSP_TREE_H

#include "../hitRecord.h"
#include "../ray.h"
#include "intersectable.h"
#include "math/vector3f.h"
#include "boundingBox.h"

#include <vector>

/**
 * An acceleration data-structure that performs a spatial sibdivision via
 * binary space partition trees.
 */
class BspTree : public Intersectable {
 private:
   const Intersectable& intersectable;
 public:
  BspTree(const Intersectable&);
  HitRecord* intersect(const Ray& ray) const;
  BoundingBox getBoundingBox() const;
};
#endif
