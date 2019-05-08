#include "intersectables/csg/csgNode.h"
#include <algorithm>
#include "ray.h"

CsgNode::CsgNode(const CsgSolid* left, const CsgSolid* right, SetOperation operation)
    : left(left), right(right), operation(operation) {}

std::vector<CsgNode::IntervalBoundary> CsgNode::getIntervalBoundaries(const Ray& ray) const {
  std::vector<CsgNode::IntervalBoundary> combined;

  auto leftIntervals = left->getIntervalBoundaries(ray);
  auto rightIntervals = right->getIntervalBoundaries(ray);

  // mark interval boundaries as left- or right node
  for (auto& leftInterval : leftIntervals) {
    leftInterval.belongsTo = BelongsTo::LEFT;
  }

  for (auto& rightInterval : rightIntervals) {
    rightInterval.belongsTo = BelongsTo::RIGHT;
  }

  combined.insert(combined.end(), leftIntervals.begin(), leftIntervals.end());
  combined.insert(combined.end(), rightIntervals.begin(), rightIntervals.end());

  // Sort members according to "<" operator defined in IntervalBoundary struct
  std::sort(combined.begin(), combined.end());

  bool inLeft = false;
  bool inRight = false;
  for (auto& interval : combined) {
    if (interval.belongsTo == BelongsTo::LEFT) {
      inLeft = interval.type == BoundaryType::START;
    }

    if (interval.belongsTo == BelongsTo::RIGHT) {
      inRight = interval.type == BoundaryType::START;
    }

    switch (operation) {
      case INTERSECTION:
        interval.type = (inLeft && inRight) ? BoundaryType::START : BoundaryType::END;
        break;
      case UNION:
        interval.type = (inLeft || inRight) ? BoundaryType::START : BoundaryType::END;
        break;
      case DIFFERENCE:
        interval.type = (inLeft && !inRight) ? BoundaryType::START : BoundaryType::END;

        // In a subtract operation, the subtracted solid is turned inside out,
        // or it "switches sign", so we need to flip its normal direction
        if (interval.belongsTo == BelongsTo::RIGHT && interval.hitRecord->isValid()) {
          interval.hitRecord->normal->negate();
        }
        break;
    }
  }

  // clean up
  CsgSolid::IntervalBoundary prev;
  prev.type = BoundaryType::END;
  std::vector<CsgNode::IntervalBoundary> finalCombination;
  for (auto& interval : combined) {
    if (interval.type != prev.type || interval.type == BoundaryType::UNKOWN) {
      finalCombination.push_back(interval);
    }
    prev.type = interval.type;
  }

  return finalCombination;
}
