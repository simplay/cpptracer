#include "intersectables/geometries/plane.h"
#include <cmath>

Plane::Plane(Material* material, const Vector3f& normal, float distance)
    : material(material), normal(normal), distance(distance), aabb(initBoundingBox()) {}

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
      b2.t = (hit->t > 0.0) ? std::numeric_limits<float>::max() : -std::numeric_limits<float>::max();

    } else {
      b1.type = BoundaryType::END;
      b2.type = BoundaryType::START;

      // If the t value of the END boundary was positive, then the t value of
      // the START boundary is negative
      b2.t = (hit->t > 0.0) ? -std::numeric_limits<float>::max() : std::numeric_limits<float>::max();
    }

    boundaries.push_back(b1);
    boundaries.push_back(b2);
  }

  return boundaries;
}
