#ifndef PLANE_H
#define PLANE_H

#include <limits>
#include "../hitRecord.h"
#include "../math/vector3f.h"
#include "../ray.h"
#include "boundingBox.h"
#include "intersectable.h"

class Material;

// Construct a plane given its normal and distance to the origin Note that the
// distance is along the direction that the normal points (meaning that the
// sign of distance matters)
class Plane : public Intersectable {
 private:
  BoundingBox initBoundingBox() {
    return BoundingBox(Vector3f(std::numeric_limits<float>::min()),
                       Vector3f(std::numeric_limits<float>::max()));
  }

 protected:
  const float EPSILON = 0.000001;

  Material* material;

  // normal of the plane
  const Vector3f normal;

  // distance to origin measured along normal direction
  const float distance;

  BoundingBox aabb;

 public:
  Plane(Material*, const Vector3f&, float);
  // plane-ray intersection ray: p(t) = orig + t * dir
  //
  // Implicit plane:
  // f(p) = dot(n, (p - a)) intersection:
  // f(p(t)) = 0. Solve for t.  Plug t_i into
  // p(t_i) will give intersection point
  virtual HitRecord* intersect(const Ray& ray) const;

  const BoundingBox& getBoundingBox() const { return aabb; }
};
#endif
