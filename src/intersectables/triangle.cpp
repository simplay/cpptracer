#include <iostream>
#include "triangle.h"
#include "matrix3f.h"

Triangle::Triangle(Material* material, Point3f* a, Point3f* b, Point3f* c)
  : material(material), a(a), b(b), c(c) {}

Point3f* Triangle::computeNormal(float, float) {
  Point3f ba(b);
  ba.sub(a);

  Point3f ca(c);
  ca.sub(a);

  auto normal = ba.cross(&ca);
  normal->normalize();

  return normal;
}

HitRecord* Triangle::intersect(Ray* ray) {
  Point3f* ab = new Point3f(a);
  ab->sub(b);

  Point3f* ac = new Point3f(a);
  ac->sub(c);

  Point3f* ao = new Point3f(a);
  ao->sub(ray->origin);

  Matrix3f m(
    ab->x, ac->x, ray->direction->x,
    ab->y, ac->y, ray->direction->y,
    ab->z, ac->z, ray->direction->z
  );

  delete ab;
  delete ac;

  Matrix3f* invM = m.inv();
  Point3f y(ao->x, ao->y, ao->z);

  delete ao;

  // matrix vector multiplication: A * params = y
  Point3f* params = invM->mult(&y);
  delete invM;

  // Perform conservative inside-outside check
  if (params->x < 0 || params->x > 1) {
    delete params;
    return new HitRecord();
  }

  if (params->y < 0 || params->y > 1) {
    delete params;
    return new HitRecord();
  }

  // note that: alpha + beta + gamma = 1
  if (params->x + params->y > 1) {
    delete params;
    return new HitRecord();
  }

  float t = params->z;

  Point3f* intersectionPosition = new Point3f(ray->direction);
  intersectionPosition->scale(t);
  intersectionPosition->add(ray->origin);

  Point3f* wIn = new Point3f(ray->direction);
  wIn->negate();
  wIn->normalize();

  auto normal = computeNormal(params->x, params->y);
  delete params;
  return new HitRecord(
    t,
    intersectionPosition,
    normal,
    new Point3f(),
    wIn,
    material,
    this
  );
}
