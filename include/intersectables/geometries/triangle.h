#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hitRecord.h"
#include "intersectables/accelerator/boundingBox.h"
#include "intersectables/intersectable.h"
#include "math/vector3f.h"
#include "ray.h"

class Material;

// Construct a plane given its normal and distance to the origin Note that the
// distance is along the direction that the normal points (meaning that the
// sign of distance matters)
class Triangle : public Intersectable {
 private:
 protected:
  const int faceId;
  Material* material;

  // normal of the plane
  const Vector3f a;
  const Vector3f b;
  const Vector3f c;
  const BoundingBox aabb;

  virtual Vector3f* computeNormal(float alpha, float beta) const;

 public:
  Triangle(const int, Material*, const Vector3f&, const Vector3f&, const Vector3f&);

  // plane-ray intersection ray: p(t) = orig + t * dir
  //
  // Implicit plane:
  // f(p) = dot(n, (p - a)) intersection:
  // f(p(t)) = 0. Solve for t.  Plug t_i into
  // p(t_i) will give intersection point
  HitRecord* intersect(const Ray& ray) const;

  int getFaceId() const { return faceId; }

  const Vector3f& getVertexA() const { return a; }

  const Vector3f& getVertexB() const { return b; }

  const Vector3f& getVertexC() const { return c; }

  const BoundingBox& getBoundingBox() const;
};
#endif
