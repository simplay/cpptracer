#include "intersectables/csg/csgNode.h"
#include "ray.h"

CsgNode::CsgNode(const CsgSolid* left, const CsgSolid* right, SetOperation operation)
    : left(left), right(right), operation(operation) {}

std::vector<CsgNode::IntervalBoundary> CsgNode::getIntervalBoundaries(Ray r) const {
  std::vector<CsgNode::IntervalBoundary> combined(100);

  return combined;
}
