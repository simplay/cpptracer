#include "intersectables/bspTree.h"
#include <cmath>

namespace {
int computeMaxDepth(const IntersectableList& intersectables) {
  return (int)std::round(8.0 + 1.3 * std::log(intersectables.size()));
}

BspNode buildTree(const IntersectableList& intersectables, const BoundingBox& boundingBox,
                  Axis::Label axis, float depth) {
  return BspNode(1, intersectables.getBoundingBox(), axis);
}
}  // namespace

BspTree::BspTree(const IntersectableList& intersectables, int maxIntersectablesPerNode,
                 int maxDepth)
    : root(buildTree(intersectables, intersectables.getBoundingBox(), Axis::Label::X, 0)),
      intersectables(intersectables),
      maxDepth(maxDepth),
      maxIntersectablesPerNode(maxIntersectablesPerNode),
      aabb(initBoundingBox()) {}

BspTree::BspTree(const IntersectableList& intersectables)
    : BspTree(intersectables, 5, computeMaxDepth(intersectables)) {}

HitRecord* BspTree::intersect(const Ray& ray) const { return new HitRecord(); }

const BoundingBox& BspTree::getBoundingBox() const { return aabb; }
