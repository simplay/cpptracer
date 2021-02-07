#ifndef CUBE_H
#define CUBE_H

#include <limits>
#include "hitRecord.h"
#include "math/vector3f.h"
#include "intersectables/intersectable.h"
#include "intersectables/accelerator/boundingBox.h"
#include "ray.h"

class Material;

class Cube : public Intersectable {
 private:
  const Material* material;
  const Vector3f bottomLeft;
  const Vector3f topRight;
  const BoundingBox aabb;

  BoundingBox computeAABB() {
    return BoundingBox(Vector3f(std::numeric_limits<float>::min()),
        Vector3f(std::numeric_limits<float>::max()));
  }

 public:
  Cube(const Material* material, const Vector3f& bottomLeft, const Vector3f& topRight);
  HitRecord* intersect(const Ray& ray) const;
  const BoundingBox& getBoundingBox() const { return aabb; }
};
#endif
