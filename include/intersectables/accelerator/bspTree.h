#ifndef BSP_TREE_H
#define BSP_TREE_H

#include "boundingBox.h"
#include "bspNode.h"
#include "hitRecord.h"
#include "intersectables/containers/intersectableList.h"
#include "intersectables/intersectable.h"
#include "math/vector3f.h"
#include "ray.h"

#include <vector>

struct BspStrackItem {
  const BspNode* node;
  float tmin, tmax, tsplit;
};

/**
 * An acceleration data-structure that performs a spatial sibdivision via
 * binary space partition trees.
 */
class BspTree : public Intersectable {
 private:
  const float kEps = 0.001;

  const BspNode* root;
  const IntersectableList* intersectables;
  const unsigned maxIntersectablesPerNode;
  const unsigned maxDepth;
  BoundingBox aabb;
  BoundingBox initBoundingBox() { return BoundingBox(Vector3f(0, 0, 0), Vector3f(0, 0, 0)); }
  BspNode* buildTree(const IntersectableList* intersectables, const BoundingBox* boundingBox,
                     Axis::Label axis, float depth, unsigned maxIntersectablesPerNode,
                     unsigned maxDepth);

 public:
  BspTree(const IntersectableList*, unsigned maxIntersectablesPerNode, unsigned maxDepth);
  BspTree(const IntersectableList*);
  HitRecord* intersect(const Ray& ray) const;
  const BoundingBox& getBoundingBox() const;
  const BspNode* getRoot() const { return root; }
};
#endif
