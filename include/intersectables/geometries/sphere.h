#ifndef SPHERE_H
#define SPHERE_H

#include "hitRecord.h"
#include "intersectables/accelerator/boundingBox.h"
#include "intersectables/intersectable.h"
#include "math/vector3f.h"
#include "ray.h"

class Material;

class Sphere : public Intersectable {
 private:
  Material* material;
  const Vector3f center;
  const float radius;
  const BoundingBox aabb;

  BoundingBox computeAABB(const Vector3f& center, float radius) {
    auto bottomLeft = Vector3f(center);
    auto shift = Vector3f(-radius, -radius, -radius);
    bottomLeft.add(shift);

    auto topRight = Vector3f(center);
    shift = Vector3f(radius, radius, radius);
    topRight.add(shift);

    return BoundingBox(bottomLeft, topRight);
  }

 public:
  Sphere(Material*, const Vector3f&, float);
  virtual HitRecord* intersect(const Ray& ray) const;

  const BoundingBox& getBoundingBox() const { return aabb; }
};
#endif
