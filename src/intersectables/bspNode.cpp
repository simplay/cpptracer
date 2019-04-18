#include "intersectables/bspNode.h"

namespace {
std::vector<Intersectable> initObjects() {
  auto objects = std::vector<Intersectable>();
  return objects;
}
}  // namespace

BspNode::BspNode(float planePosition, const BoundingBox& boundingBox, Axis::Label axis)
    : planePosition(planePosition), boundingBox(boundingBox), axis(axis), objects(initObjects()) {}

std::array<float, 2> BspNode::intersect(const Ray& ray) const {
  std::array<float, 2> intersections;
  return intersections;
}

const BoundingBox& BspNode::getBoundingBox() const { return boundingBox; }
