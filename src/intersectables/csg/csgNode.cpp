#include "intersectables/csg/csgNode.h"
#include <algorithm>
#include "ray.h"

CsgNode::CsgNode(const CsgSolid* left, const CsgSolid* right, SetOperation operation)
    : left(left), right(right), operation(operation) {}

std::vector<CsgNode::IntervalBoundary> CsgNode::getIntervalBoundaries(Ray ray) const {
  std::vector<CsgNode::IntervalBoundary> combined(100);

  auto leftIntervals = left->getIntervalBoundaries(ray);
  auto rightIntervals = right->getIntervalBoundaries(ray);

  // mark interval boundaries as left- or right node
  for (auto& leftInterval : leftIntervals) {
    leftInterval.belongsTo = BelongsTo::LEFT;
  }

  for (auto& rightInterval : leftIntervals) {
    rightInterval.belongsTo = BelongsTo::RIGHT;
  }

  combined.insert(std::end(leftIntervals), std::begin(leftIntervals), std::end(leftIntervals));
  combined.insert(std::end(rightIntervals), std::begin(rightIntervals), std::end(rightIntervals));

  // Sort members according to "<" operator defined in IntervalBoundary struct
  std::sort(combined.begin(), combined.end());

  bool inLeft = false;
  bool inRight = false;
  for (auto& interval : combined) {
    inLeft = interval.belongsTo == BelongsTo::LEFT && interval.type == BoundaryType::START;
    inRight = interval.belongsTo == BelongsTo::RIGHT && interval.type == BoundaryType::START;

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
  std::vector<CsgNode::IntervalBoundary> finalCombination(100);
  for (auto& interval : combined) {
    if (interval.type != prev.type) {
      finalCombination.push_back(interval);
    }
    prev.type = interval.type;
  }

  return combined;
}
