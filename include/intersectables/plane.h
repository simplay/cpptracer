#include "intersectable.h"
#include "../math/point3f.h"
#include "../hitRecord.h"
#include "../ray.h"

class Material;

#ifndef PLANE_H
#define PLANE_H

// Construct a plane given its normal and distance to the origin Note that the
// distance is along the direction that the normal points (meaning that the
// sign of distance matters)
class Plane : public Intersectable {
  const float EPSILON = 0.000001;

  public:
    Material* material;

    // normal of the plane
    Point3f* normal;

    // distance to origin measured along normal direction
    float distance;

    Plane(Material*, Point3f*, float);
    // plane-ray intersection ray: p(t) = orig + t * dir
    //
    // Implicit plane:
    // f(p) = dot(n, (p - a)) intersection:
    // f(p(t)) = 0. Solve for t.  Plug t_i into
    // p(t_i) will give intersection point
    virtual HitRecord* intersect(Ray* ray) const;
};

#endif
