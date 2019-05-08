#ifndef CSG_NODE_H
#define CSG_NODE_H

#include "intersectables/csg/csgSolid.h"

enum SetOperation { UNION = 0, INTERSECTION = 1, DIFFERENCE = 2 };

/**
 * A CsgNode combines two CsgSolid instances by a binary set operation: Either
 * by a union-, intersection or difference- operation.
 */
class CsgNode : public CsgSolid {

 private:
  const CsgSolid* left;
  const CsgSolid* right;
  const SetOperation operation;

 public:
  CsgNode(const CsgSolid* left, const CsgSolid* right, SetOperation operation);

  std::vector<IntervalBoundary> getIntervalBoundaries(const Ray& ray) const;

};
#endif
