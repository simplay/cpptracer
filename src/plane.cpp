#include "plane.h"
#include <iostream>
#include <cmath>

Plane::Plane(Material* material, Point3f* normal, float distance)
  : material(material), normal(normal), distance(distance)
{}

HitRecord* Plane::intersect(Ray* ray) {
  float epsilon = 0.000001;

  // incident angle: angle between the ray direction and the plane normal
  auto cosTheta = normal->dot(ray->direction);
  if (std::abs(cosTheta) <= epsilon) {
    return new HitRecord();
  }

  float t = -(normal->dot(ray->origin) + distance) / cosTheta;
  if (t <= 0) {
    return new HitRecord();
  }

  Point3f* intersectionPosition = new Point3f(ray->direction);
  intersectionPosition->scale(t);
  intersectionPosition->add(ray->origin);

  Point3f* wIn = new Point3f(ray->direction);
  wIn->negate();
  wIn->normalize();

  // do something more

  Point3f* hitNormal = new Point3f(normal);
  Point3f tangent = (new Point3f(1, 0, 0))->cross(hitNormal);

  return new HitRecord(
      t,
      intersectionPosition,
      hitNormal,
      &tangent,
      wIn,
      material,
      this
  );
}
