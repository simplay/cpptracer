#include "intersectables/geometries/cylinder.h"
#include <cmath>
#include <iostream>

HitRecord* Cylinder::buildHitRecord(float t, const Ray& ray) const {
  auto hitPosition = ray.pointAt(t);
  auto hitNormal = new Vector3f(*hitPosition);

  auto wIn = Vector3f().incidentDirection(*ray.direction);

  // clang-format off
  return new HitRecord(
      t,
      hitPosition,
      hitNormal,
      new Vector3f(),
      wIn,
      material,
      this,
      ray.i,
      ray.j
      );
  // clang-format on
}

Cylinder::Cylinder(Material* material) : material(material), aabb(computeAABB()) {}

HitRecord* Cylinder::intersect(const Ray& ray) const {
  auto rdx = ray.direction->x;
  auto rdy = ray.direction->y;

  auto rex = ray.origin->x;
  auto rey = ray.origin->y;

  float a = rdx * rdx + rdy * rdy;
  float b = 2.0 * rex * rdx + 2.0 * rey * rdy;
  float c = rex * rex + rey * rey - 1;

  float discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return new HitRecord();
  } else {
    float t1 = (-b + sqrt(discriminant)) / (2.0 * a);
    float t2 = (-b - sqrt(discriminant)) / (2.0 * a);

    float t = std::min(t1, t2);
    if (t < 0) {
      t = std::max(t1, t2);
      if (t < 0) {
        return new HitRecord();
      }
    }

    return buildHitRecord(t, ray);
  }
}

std::vector<CsgSolid::IntervalBoundary> Cylinder::getIntervalBoundaries(const Ray& ray) const {
  std::vector<IntervalBoundary> boundaries;
  auto rdx = ray.direction->x;
  auto rdy = ray.direction->y;

  auto rex = ray.origin->x;
  auto rey = ray.origin->y;

  float a = rdx * rdx + rdy * rdy;
  float b = 2.0 * rex * rdx + 2.0 * rey * rdy;
  float c = rex * rex + rey * rey - 1;

  float discriminant = b * b - 4 * a * c;

  if (discriminant < 0) {
    return boundaries;
  }

  float t1 = (-b + sqrt(discriminant)) / (2.0 * a);
  float t2 = (-b - sqrt(discriminant)) / (2.0 * a);

  auto hit1 = buildHitRecord(t1, ray);
  IntervalBoundary b1;
  b1.t = hit1->t;
  b1.type = findBoundaryType(hit1, ray);
  b1.hitRecord = hit1;

  auto hit2 = buildHitRecord(t2, ray);
  IntervalBoundary b2;
  b2.t = hit2->t;
  b2.type = findBoundaryType(hit2, ray);
  b2.hitRecord = hit2;

  boundaries.push_back(b1);
  boundaries.push_back(b2);

  return boundaries;
}
