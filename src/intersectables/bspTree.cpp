#include "intersectables/bspTree.h"
#include <cmath>
#include <iostream>
#include <limits>
#include <stack>

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

float computeRaySplitPlaneIntersectionParam(const Ray& ray, const BspNode& node) {
  // no split plane exists for leafs
  if (node.getIsLeaf()) {
    return std::numeric_limits<float>::quiet_NaN();
  }

  auto originParam = Axis::valueOf(node.getAxis(), *ray.origin);
  auto distanceParam = Axis::valueOf(node.getAxis(), *ray.direction);

  return (node.getPlanePositionParam() - originParam) / distanceParam;
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

HitRecord* BspTree::intersect(const Ray& ray) const {
  float EPSILON = 0.001;
  std::stack<BspStrackItem> stack;
  auto hits = root.intersect(ray);
  if (hits.size() == 0) {
    return new HitRecord();
  }
  HitRecord* closest = new HitRecord();

  float tmin = hits[0];
  float tmax = hits[1];
  float t = std::numeric_limits<float>::max();

  std::cout << root.getIsLeaf() << std::endl;
  const BspNode* node = &root;
  while (node != nullptr) {
    if (t < tmin) {
      break;
    }

    if (!node->getIsLeaf()) {
      float tsplit = computeRaySplitPlaneIntersectionParam(ray, *node);

      const BspNode* first = node->getAbove();
      const BspNode* second = node->getBelow();
      auto v = Axis::valueOf(node->getAxis(), *ray.origin);
      if (v < node->getPlanePositionParam()) {
        first = node->getBelow();
        second = node->getAbove();
      }

      // case 1: only first child is hit
      if (tsplit > tmax || tsplit < 0 ||
          (std::abs(tsplit) < EPSILON && !first->intersect(ray).empty())) {
        node = first;
        // case 2: only second child is hit
      } else if (tsplit < tmin || (std::abs(tsplit) < EPSILON && !second->intersect(ray).empty())) {
        node = second;

        // case 3: both children are hit
      } else {
        node = first;
        BspStrackItem item;
        item.node = second;
        item.tmin = tsplit;
        item.tmax = tmax;

        stack.push(item);
        tmax = tsplit;
      }
    } else {
      auto hit = node->getIntersectables().intersect(ray);
      if (hit->isValid() && hit->t < t && hit->t > 0.0) {
        closest = hit;
        t = hit->t;
      }

      if (stack.empty()) {
        break;
      }

      auto i = stack.top();
      stack.pop();
      node = i.node;
      tmin = i.tmin;
      tmax = i.tmax;
    }
  }

  return closest;
}

const BoundingBox& BspTree::getBoundingBox() const { return aabb; }
