#include "intersectables/csg/csgInstance.h"
#include <memory>

CsgInstance::CsgInstance(CsgSolid* solid) : Instance(solid), solid(solid) {}

CsgInstance::CsgInstance(CsgSolid* solid, Matrix4f* transformation)
    : Instance(solid, transformation), solid(solid) {}

std::vector<CsgSolid::IntervalBoundary> CsgInstance::getIntervalBoundaries(const Ray& ray) const {
  std::vector<IntervalBoundary> boundaries;
  auto transRay = std::unique_ptr<Ray>(ray.transform(invTransformation));
  auto intervalBoundaries = solid->getIntervalBoundaries(*transRay);

  for (auto& interval : intervalBoundaries) {
    auto hit = interval.hitRecord;
    if (hit->isValid()) {
      auto finalHit = hit->transform(transformation, invTrasnposedTransformation);
      interval.hitRecord = finalHit;
    }
  }

  return boundaries;
}
