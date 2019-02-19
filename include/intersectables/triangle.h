#include "intersectable.h"
#include "../math/point3f.h"
#include "../hitRecord.h"
#include "../ray.h"

class Material;

#ifndef TRIANGLE_H
#define TRIANGLE_H

// Construct a plane given its normal and distance to the origin Note that the
// distance is along the direction that the normal points (meaning that the
// sign of distance matters)
class Triangle : public Intersectable {
  public:
    Material* material;

    // normal of the plane
    Point3f* a;
    Point3f* b;
    Point3f* c;

    virtual Point3f* computeNormal();

    Triangle(Material*, Point3f*, Point3f*, Point3f*);
    // plane-ray intersection ray: p(t) = orig + t * dir
    //
    // Implicit plane:
    // f(p) = dot(n, (p - a)) intersection:
    // f(p(t)) = 0. Solve for t.  Plug t_i into
    // p(t_i) will give intersection point
    virtual HitRecord* intersect(Ray* ray);
};

#endif
