#include "intersectables/csg/csgSolid.h"

HitRecord* CsgSolid::intersect(const Ray& ray) const {
  // TODO: implement me
  return new HitRecord();
}

const BoundingBox& CsgSolid::getBoundingBox() const {
  return aabb;
}
