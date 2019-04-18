#ifndef BSP_TREE_H
#define BSP_TREE_H

#include <array>
#include <vector>
#include "intersectables/axis.h"
#include "intersectables/boundingBox.h"
#include "intersectables/intersectable.h"
#include "ray.h"

class BspNode {
 private:
  const float planePosition;
  const BoundingBox boundingBox;
  const Axis::Label axis;
  const std::vector<Intersectable> objects;

 public:
  BspNode below();
  BspNode above();

  BspNode(float planePosition, const BoundingBox& boundingBox, Axis::Label axis);
  const BoundingBox& getBoundingBox() const;
  std::array<float, 2> intersect(const Ray&) const;
};

#endif
