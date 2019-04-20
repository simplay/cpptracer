#include "intersectables/bspTree.h"
#include <cmath>
#include <iostream>

namespace {
int computeMaxDepth(const IntersectableList& intersectables) {
  return (int)std::round(8.0 + 1.3 * std::log(intersectables.size()));
}

int computeSplitPlanePosition(const IntersectableList& intersectables, Axis::Label axis) {
  Vector3f centroid(0);
  for (auto* intersectable : intersectables.getContainer()) {
    auto bb = intersectable->getBoundingBox();
    centroid.add(bb.center());
  }
  centroid.scale(1.0 / intersectables.size());
  return Axis::valueOf(axis, centroid);
}

}  // namespace

BspNode BspTree::buildTree(const IntersectableList& currentIntersectables,
                           const BoundingBox& boundingBox, Axis::Label currentAxis, float depth,
                           unsigned maxIntersectablesPerNode, unsigned maxDepth) {
  // terminate recursion and build a leaf node
  if (depth == maxDepth || currentIntersectables.size() <= maxIntersectablesPerNode) {
    return BspNode(boundingBox, currentIntersectables);
  }

  // Split the bounding box into left and right subtree

  float splitPosition = computeSplitPlanePosition(currentIntersectables, currentAxis);
  auto boxes = boundingBox.split(currentAxis, splitPosition);
  auto leftBoundingBox = boxes[0];
  auto rightBoundingBox = boxes[1];

  IntersectableList leftIntersectables;
  IntersectableList rightIntersectables;

  for (auto* intersectable : currentIntersectables.getContainer()) {
    auto bb = intersectable->getBoundingBox();
    if (bb.overlaps(leftBoundingBox)) {
      leftIntersectables.put(intersectable);
    }

    if (bb.overlaps(rightBoundingBox)) {
      rightIntersectables.put(intersectable);
    }
  }

  auto nextAxis = Axis::nextLabel(currentAxis);
  BspNode left = buildTree(leftIntersectables, leftBoundingBox, nextAxis, depth + 1,
                           maxIntersectablesPerNode, maxDepth);
  BspNode right = buildTree(rightIntersectables, rightBoundingBox, nextAxis, depth + 1,
                            maxIntersectablesPerNode, maxDepth);

  auto currentNode =
      BspNode(splitPosition, boundingBox, currentAxis, currentIntersectables, &left, &right);
  return currentNode;
}

BspTree::BspTree(const IntersectableList& intersectables, unsigned maxIntersectablesPerNode,
                 unsigned maxDepth)
    : root(buildTree(intersectables, intersectables.getBoundingBox(), Axis::Label::X, 0,
                     maxIntersectablesPerNode, maxDepth)),
      intersectables(intersectables),
      maxIntersectablesPerNode(maxIntersectablesPerNode),
      maxDepth(maxDepth),
      aabb(initBoundingBox()) {}

BspTree::BspTree(const IntersectableList& intersectables)
    : BspTree(intersectables, 5, computeMaxDepth(intersectables)) {}

HitRecord* BspTree::intersect(const Ray& ray) const { return new HitRecord(); }

const BoundingBox& BspTree::getBoundingBox() const { return aabb; }
