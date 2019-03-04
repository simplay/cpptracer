#include <memory>
#include <iostream>
#include "triangle.h"
#include "matrix3f.h"

Triangle::Triangle(int faceId, Material* material, Point3f* a, Point3f* b, Point3f* c)
  : faceId(faceId), material(material), a(a), b(b), c(c) {}

Point3f* Triangle::computeNormal(float, float) const {
  Point3f ba(b);
  ba.sub(a);

  Point3f ca(c);
  ca.sub(a);

  auto normal = ba.cross(&ca);
  normal->normalize();

  return normal;
}

HitRecord* Triangle::intersect(Ray* ray) const {
  Point3f ab = Point3f(a);
  ab.sub(b);

  Point3f ac = Point3f(a);
  ac.sub(c);

  Point3f ao = Point3f(a);
  ao.sub(ray->origin);

  // Interpret a triangle with an infinite plane with constraints (given by
  // alpha and beta)
  Matrix3f m(
    ab.x, ac.x, ray->direction->x,
    ab.y, ac.y, ray->direction->y,
    ab.z, ac.z, ray->direction->z
  );

  auto invM = std::unique_ptr<Matrix3f>(m.inv());

  // matrix vector multiplication: A * params = y
  auto params = std::unique_ptr<Point3f>(invM->mult(&ao));

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

  auto intersectionPosition = ray->pointAt(t);
  auto wIn = Point3f().incidentDirection(ray->direction);
  auto normal = computeNormal(params->x, params->y);

  auto hit = new HitRecord(
    t,
    intersectionPosition,
    normal,
    new Point3f(),
    wIn,
    material,
    this
  );
  return hit;
}
