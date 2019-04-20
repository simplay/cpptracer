#include "intersectables/bspNode.h"

BspNode::BspNode(float planePosition, const BoundingBox& boundingBox, Axis::Label axis,
                 const IntersectableList& intersectables, const BspNode* below,
                 const BspNode* above)
    : planePosition(planePosition),
      boundingBox(boundingBox),
      axis(axis),
      intersectables(intersectables),
      isLeaf(false),
      above(above),
      below(below) {}

BspNode::BspNode(const BoundingBox& boundingBox, const IntersectableList& intersectables)
    : planePosition(0),
      boundingBox(boundingBox),
      axis(Axis::Label::X),
      intersectables(intersectables),
      isLeaf(true),
      above(nullptr),
      below(nullptr) {}

std::array<float, 2> BspNode::intersect(const Ray& ray) const {
  std::array<float, 2> intersections;
  return intersections;
}

const BoundingBox& BspNode::getBoundingBox() const { return boundingBox; }
