#include <iostream>
#include <cmath>
#include "plane.h"

Plane::Plane(Material* material, const Vector3f& normal, float distance)
  : material(material), normal(normal), distance(distance)
{}

/**
 * The distance D between a point p and a plane can be computed by:
 * D := dot((p - a), n) [0]
 * where n is a unit normal on the plane, and a is a reference point on the
 * plane
 *
 * Notice: dot((p - a), n) = 0 gives us all points p on the plane
 *
 * A point on ray is given by the parametrization
 * r(t) = o + t*d [1] where
 * o := (ox, oy, oz) denotes the origin of the ray and
 * d := (dx, dy, dz) denotes the direction of the ray and
 * t is float-valued parameter
 *
 * We can compute the distance between a point on the ray and the plane by
 * setting p = r(t), which gives us: D = dot(o + t*d - a)
 * t = dot(a - o, n) / dot(d, n) and a = (0, 0, D)
 *
 */
HitRecord* Plane::intersect(Ray* ray) const {
  // incident angle: angle between the ray direction and the plane normal
  auto cosTheta = ray->direction->dot(&normal);

  if (std::abs(cosTheta) <= EPSILON) {
    return new HitRecord();
  }

  // assumption: point is zero and then we shift by distance
  float t = -(ray->origin->dot(&normal) + distance) / cosTheta;
  if (t < 0) {
    return new HitRecord();
  }

  auto intersectionPosition = ray->pointAt(t);
  auto wIn = Vector3f().incidentDirection(ray->direction);

  auto hitNormal = new Vector3f(normal);
  auto tangent = Vector3f(1, 0, 0).cross(hitNormal);

  return new HitRecord(
    t,
    intersectionPosition,
    hitNormal,
    tangent,
    wIn,
    material,
    this
  );
}
