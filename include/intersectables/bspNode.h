#ifndef BSP_NODE_H
#define BSP_NODE_H

#include <array>
#include <vector>
#include "intersectables/axis.h"
#include "intersectables/boundingBox.h"
#include "intersectables/intersectableList.h"
#include "ray.h"

class BspNode {
 private:
  const float planePosition;
  const BoundingBox boundingBox;
  const Axis::Label axis;
  const IntersectableList& intersectables;
  bool isLeaf;
  const BspNode* above;
  const BspNode* below;

 public:
  BspNode();
  BspNode(float planePosition, const BoundingBox& boundingBox, Axis::Label axis,
          const IntersectableList& intersectables, const BspNode* below, const BspNode* above);

  BspNode(const BoundingBox& boundingBox, const IntersectableList&);
  const BoundingBox& getBoundingBox() const;
  std::array<float, 2> intersect(const Ray&) const;
};

#endif
