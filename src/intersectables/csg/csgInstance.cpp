#include "intersectables/csg/csgInstance.h"
#include <memory>

CsgInstance::CsgInstance(CsgSolid* solid)
    : solid(solid), transformation(Matrix4f().eye()), aabb(solid->getBoundingBox()) {
  this->invTransformation = Matrix4f().eye();
  this->invTrasnposedTransformation = Matrix4f().eye();
}

CsgInstance::CsgInstance(CsgSolid* solid, Matrix4f* transformation)
    : solid(solid),
      transformation(transformation),
      aabb(solid->getBoundingBox().transform(*transformation)) {
  this->invTransformation = transformation->inv();
  this->invTrasnposedTransformation = invTransformation->transposed();
}

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

HitRecord* CsgInstance::intersect(const Ray& ray) const {
  auto transRay = std::unique_ptr<Ray>(ray.transform(invTransformation));

  auto hit = solid->intersect(*transRay);
  if (!hit->isValid()) {
    return hit;
  }

  auto finalHit = hit->transform(transformation, invTrasnposedTransformation);
  delete hit;

  return finalHit;
}

const BoundingBox& CsgInstance::getBoundingBox() const { return aabb; }
