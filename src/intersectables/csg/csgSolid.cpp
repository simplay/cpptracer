#include "intersectables/csg/csgSolid.h"

HitRecord* CsgSolid::intersect(const Ray& ray) const {
  auto intervalBoundaries = getIntervalBoundaries(ray);

  // Return the first hit in front of the camera, that is, make sure
  // the hit is along the positive ray direction
  for (auto const& intervalBoundary : intervalBoundaries) {
    auto hit = intervalBoundary.hitRecord;
    if (hit->isValid() && hit->t > 0.0) {
      return hit;
    }
  }
  return new HitRecord();
}

const BoundingBox& CsgSolid::getBoundingBox() const {
  return aabb;
}
