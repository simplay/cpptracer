#include "intersectables/csg/csgNode.h"

CsgNode::CsgNode(const CsgSolid& left, const CsgSolid& right, SetOperation operation)
    : left(left), right(right), operation(operation) {}
