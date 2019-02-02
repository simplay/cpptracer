#include <iostream>
#include "triangle.h"
#include "matrix3f.h"

Triangle::Triangle(Material* material, Point3f* a, Point3f* b, Point3f* c)
  : material(material), a(a), b(b), c(c) {}

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
  Matrix3f* invM = m.inv();
  Point3f b(ao->x, ao->y, ao->z);

  Point3f* params = invM->mult(&b);

  // Perform conservative inside-outside check
  if (params->x < 0 || params->x > 1) {
    return new HitRecord();
  }

  if (params->y < 0 || params->y > 1) {
    return new HitRecord();
  }

  // note that: alpha + beta + gamma = 1
  if (params->x + params->y > 1) {
    return new HitRecord();
  }

  float t = params->z;
  Point3f* intersectionPosition = new Point3f(ray->direction);
  intersectionPosition->scale(t);
  intersectionPosition->add(ray->origin);

  Point3f* wIn = new Point3f(ray->direction);
  wIn->negate();
  wIn->normalize();

  Point3f* normal = ab->cross(ac);
  normal->normalize();

  return new HitRecord(
    t,
    intersectionPosition,
    normal,
    NULL,
    wIn,
    material,
    this
  );
}
