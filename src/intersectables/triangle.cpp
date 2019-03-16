#include "intersectables/triangle.h"
#include <iostream>
#include <memory>
#include "math/matrix3f.h"

Triangle::Triangle(int faceId, Material* material, const Vector3f& a, const Vector3f& b,
                   const Vector3f& c)
    : faceId(faceId), material(material), a(a), b(b), c(c) {}

Vector3f* Triangle::computeNormal(float, float) const {
  Vector3f ba(b);
  ba.sub(a);

  Vector3f ca(c);
  ca.sub(a);

  auto normal = ba.cross(ca);
  normal->normalize();

  return normal;
}

HitRecord* Triangle::intersect(const Ray& ray) const {
  Vector3f ab = Vector3f(a);
  ab.sub(b);

  Vector3f ac = Vector3f(a);
  ac.sub(c);

  Vector3f ao = Vector3f(a);
  ao.sub(*ray.origin);

  // clang-format off
  // Interpret a triangle with an infinite plane with constraints (given by
  // alpha and beta)
  Matrix3f m(ab.x, ac.x, ray.direction->x,
             ab.y, ac.y, ray.direction->y,
             ab.z, ac.z, ray.direction->z);
  // clang-format on

  auto invM = std::unique_ptr<Matrix3f>(m.inv());

  // matrix vector multiplication: A * params = y
  auto params = std::unique_ptr<Vector3f>(invM->mult(ao));

  // Perform conservative inside-outside check
  if (params->x <= 0 || params->x >= 1) {
    return new HitRecord();
  }

  if (params->y <= 0 || params->y >= 1) {
    return new HitRecord();
  }

  // note that: alpha + beta + gamma = 1
  auto sum = params->x + params->y;
  if (sum >= 1.0 || sum <= 0.0) {
    return new HitRecord();
  }

  float t = params->z;

  auto intersectionPosition = ray.pointAt(t);
  auto wIn = Vector3f().incidentDirection(*ray.direction);
  auto normal = computeNormal(params->x, params->y);

  // clang-format off
  auto hit = new HitRecord(
    t,
    intersectionPosition,
    normal,
    new Vector3f(),
    wIn,
    material,
    this
  );
  // clang-format on
  return hit;
}
