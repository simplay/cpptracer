#include "../hitRecord.h"
#include "../math/vector3f.h"
#include "../ray.h"
#include "intersectable.h"

class Material;

#ifndef TRIANGLE_H
#define TRIANGLE_H

// Construct a plane given its normal and distance to the origin Note that the
// distance is along the direction that the normal points (meaning that the
// sign of distance matters)
class Triangle : public Intersectable {
 protected:
  int faceId;
  Material* material;

  // normal of the plane
  const Vector3f a;
  const Vector3f b;
  const Vector3f c;

  virtual Vector3f* computeNormal(float alpha, float beta) const;

 public:
  Triangle(int, Material*, const Vector3f&, const Vector3f&, const Vector3f&);
  // plane-ray intersection ray: p(t) = orig + t * dir
  //
  // Implicit plane:
  // f(p) = dot(n, (p - a)) intersection:
  // f(p(t)) = 0. Solve for t.  Plug t_i into
  // p(t_i) will give intersection point
  HitRecord* intersect(Ray* ray) const;
  virtual void log() const {
    std::cout << "face-index: " << faceId << std::endl;
    std::cout << "vertices: " << std::endl;
    a.log();
    b.log();
    c.log();
  }
};

#endif
