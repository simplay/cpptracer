#include "intersectables/geometries/cube.h"
#include <iostream>
#include <algorithm>

Cube::Cube(const Material* material, const Vector3f& bottomLeft, const Vector3f& topRight)
    : material(material), bottomLeft(bottomLeft), topRight(topRight), aabb(computeAABB()){}

HitRecord* Cube::intersect(const Ray& ray) const {
  float tmin = (bottomLeft.x - ray.origin->x) / ray.direction->x;
  float tmax = (topRight.x - ray.origin->x) / ray.direction->x;
  Vector3f normal(tmin, 0, 0);

  if (tmin > tmax) {
    Vector3f normal(tmax, 0, 0);
    std::swap(tmin, tmax);
  }

  float tymin = (bottomLeft.y - ray.origin->y) / ray.direction->y;
  float tymax = (topRight.y - ray.origin->y) / ray.direction->y;

  if (tymin > tymax) {
    std::swap(tymin, tymax);
  }

  if ((tmin > tymax) || (tymin > tmax)) {
    return new HitRecord();
  }

  if (tymin > tmin) {
    Vector3f normal(0, tymin, 0);
    tmin = tymin;
  }

  if (tymax < tmax) {
    Vector3f normal(0, tymax, 0);
    tmax = tymax;
  }

  float tzmin = (bottomLeft.z - ray.origin->z) / ray.direction->z;
  float tzmax = (topRight.z - ray.origin->z) / ray.direction->z;

  if (tzmin > tzmax) {
    std::swap(tzmin, tzmax);
  }

  if ((tmin > tzmax) || (tzmin > tmax)) {
    return new HitRecord;
  }

  if (tzmin > tmin) {
    Vector3f normal(0, 0, tzmin);
    tmin = tzmin;
  }

  if (tzmax < tmax) {
    Vector3f normal(0, 0, tzmax);
    tmax = tzmax;
  }

  std::cout << tmin << std::endl;
  auto wIn = Vector3f().incidentDirection(*ray.direction);
  auto intersectionPoint = ray.pointAt(tmin);

  auto n = new Vector3f(normal);
  n->normalize();

  // clang-format off
  auto hit = new HitRecord(
    tmin,
    intersectionPoint,
    n,
    new Vector3f(),
    wIn,
    material,
    this
  );
  // clang-format on

  // return something meaningful
  return hit;
}
