#include <iostream>
#include <cmath>
#include "sphere.h"

Sphere::Sphere(Material* material, Point3f* center, float radius)
  : material(material), center(center), radius(radius)
{}

/**
 * Details how to compute the ray-sphere intersection:
 *
 * A point on ray is given by the parametrization
 * r(t) = o + t*d [1] where
 * o := (ox, oy, oz) denotes the origin of the ray and
 * d := (dx, dy, dz) denotes the direction of the ray and
 * t is float-valued parameter
 *
 * the implicit formulation of the surface of a sphere is given by
 * (x-x0)^2 + (y - y0)^2 + (z - z0)^2 = r^2
 * <=>
 * ||P-C||^2 = r^2 [2] where
 * P := (x, y, z) a point on the sphere
 * C := (x0, y0, z0) denotes the center of the sphere
 *
 * Notice [1] can further be reformulated to
 * dot(P-C, P-C) = r^2 [3]
 *
 * There is an intersection IFF a point on a ray is on the surface on the sphere,
 * i.e. intersection IFF P = R(t). [4]
 * With the definitions of [1] and [3] and the fact [4] we can derive
 * ((ox - t*dx) - x0)^2 + ((oy - t*dy) - y0)^2 + ((oz - t*dz) - z0)^2 = r^2
 * by expanding and rearranging we finally get:
 * t^2 * dot(d, d) + 2*t*dot(d, o - C) + dot(o - c, o - c) - r^2 = 0 [5]
 * This is a quadratic equation of the form a*t^2 + b*t + c = 0 [6] where
 * a := dot(d, d), b := 2 * dot(d, o - C) and c := dot(o - c, o - c) - r^2
 *
 * The solutions of an equation of the form [5] is given by
 * t = -b +- sqrt(b^2 - 4*a*c) / (2*a) where
 * b^2 - 4*a*c denotes the discriminant of the equation
 *
 * If discriminant < 0 j, the line of the ray does not intersect the sphere (missed);
 * If discriminant = 0 the line of the ray just touches the sphere in one point (tangent);
 * If discriminant > 0, the line of the ray touches the sphere in two points (intersected).
 *
 * There are 3 different ways to intersect a sphere:
 *
 * 1. There is no intersection
 * 2. There is one intersection point (i.e. the ray is a tangent on the plane)
 * 3. There are two intersection points (ray penetrates the sphere):
 *  a) if both t are positive, the ray is facing the sphere and intersecting
 *  b) if one t is positive and one negative, the ray is shooting from inside
 *  c) if both t are negative, the ray is shooting away from the sphere
 *
 * For computing the hitRecord of the intersection, we are interested in the
 * smaller and positive t.
 */
HitRecord* Sphere::intersect(Ray* ray) {
  Point3f oc(ray->origin);
  oc.sub(center);

  Point3f rd(ray->direction);
  float a = rd.dot();
  float b = 2.0 * rd.dot(&oc);
  float c = oc.dot() - radius * radius;
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

    auto hitPosition = ray->pointAt(t);
    auto hitNormal = new Point3f(hitPosition);
    hitNormal->sub(center);
    hitNormal->scale(1.0 / radius);

    auto wIn = Point3f().incidentDirection(ray->direction);

    return new HitRecord(
      t,
      hitPosition,
      hitNormal,
      new Point3f(),
      wIn,
      material,
      this,
      ray->i,
      ray->j
    );
  }
}
