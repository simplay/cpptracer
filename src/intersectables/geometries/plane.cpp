#include "intersectables/geometries/plane.h"
#include <cmath>

Plane::Plane(Material* material, const Vector3f& normal, float distance)
    : material(material), normal(normal), distance(distance), aabb(initBoundingBox()) {}

/**
 * In the following a derivation of the intersection formula we are using in
 * this implementation to compute the plane ray intersection:
 *
 * A plane can be defined by a normal n and a point p0 on the plane.
 * Then, every other point p on the plane fulfills
 *
 * dot(p - p0, n) = 0
 *
 * This the implicit representation of a plane.
 *
 * A point on ray is given by the parametrization
 * r(t) = o + t*d [1] where
 * o := (ox, oy, oz) denotes the origin of the ray and
 * d := (dx, dy, dz) denotes the direction of the ray and
 * t is float-valued parameter
 *
 * By setting p = r(t) and using the plane definition, we get
 *
 * dot(r(t) - p0, n) = dot(o + t*d - p0, n) = 0
 *
 * <=>
 *
 * dot(t*d, n) + dot(o - p0, n) = 0
 *
 * because dot(t*d, n) = t*dot(d, n)
 * =>
 * t = -dot(o - p0, n) / dot(d, n)
 *   = dot(p0 - o, n) / dot(d, n)
 *
 * which is the definition of the intersection parameter t.
 *
 * However, we can further simplify the formula of t when assuming[1]
 *
 * that p0 is defined as p0 = m * n, where m denotes a scalar.
 * This is useful when we want to define a plane by a distance value m and a
 * normal n
 *
 * then dot(p0 - o, n) = dot(m*n - o, n)
 *                     = m * dot(n, n) - dot(o, n)
 *                     = m * 1 - dot(o, n)
 *                     = m - dot(o, n)
 * and hence
 * t = (m - dot(o, n)) / dot(d, n)
 *
 *
 * Remarks:
 *
 * [1] : This can only be performed, when assuming, that the normal is
 * always pointing outwards, i.e. away from the origin)
 */
HitRecord* Plane::intersect(const Ray& ray) const {
  // incident angle: angle between the ray direction and the plane normal
  auto cosTheta = ray.direction->dot(normal);

  if (std::abs(cosTheta) <= EPSILON) {
    return new HitRecord();
  }

  // assumption: point is zero and then we shift by distance
  float t = -(ray.origin->dot(normal) + distance) / cosTheta;
  if (t <= 0) {
    return new HitRecord();
  }

  auto intersectionPosition = ray.pointAt(t);
  auto wIn = Vector3f().incidentDirection(*ray.direction);

  auto hitNormal = new Vector3f(normal);
  auto tangent = Vector3f(1, 0, 0).cross(*hitNormal);

  // clang-format off
  return new HitRecord(
    t,
    intersectionPosition,
    hitNormal,
    tangent,
    wIn,
    material,
    this
  );
  // clang-format on
}

std::vector<CsgSolid::IntervalBoundary> Plane::getIntervalBoundaries(const Ray& ray) const {
  std::vector<IntervalBoundary> boundaries;

  IntervalBoundary b1, b2;
  auto hit = intersect(ray);

  if (hit->isValid()) {
    b1.hitRecord = hit;
    b1.t = hit->t;

    // Determine if ray entered or left the half-space defined by the plane.
    if (normal.dot(*ray.direction) < 0.0) {
      b1.type = BoundaryType::START;
      b2.type = BoundaryType::END;

      // If the t value of the START boundary was positive, so is the t value
      // of the END boundary
      b2.t =
          (hit->t > 0.0) ? std::numeric_limits<float>::max() : -std::numeric_limits<float>::max();

    } else {
      b1.type = BoundaryType::END;
      b2.type = BoundaryType::START;

      // If the t value of the END boundary was positive, then the t value of
      // the START boundary is negative
      b2.t =
          (hit->t > 0.0) ? -std::numeric_limits<float>::max() : std::numeric_limits<float>::max();
    }

    boundaries.push_back(b1);
    boundaries.push_back(b2);
  }

  return boundaries;
}
