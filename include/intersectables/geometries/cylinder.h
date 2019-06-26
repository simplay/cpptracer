#ifndef CYLINDER_H
#define CYLINDER_H

#include "hitRecord.h"
#include "intersectables/accelerator/boundingBox.h"
#include "intersectables/csg/csgSolid.h"
#include "math/vector3f.h"
#include "ray.h"

class Material;

/**
 * Infinite cylinder along z-axis with radius 1.
 **/
class Cylinder : public CsgSolid {
 private:
  Material* material;
  const BoundingBox aabb;
  float radius;

  BoundingBox computeAABB() {
    Vector3f center(0, 0, 0);
    auto bottomLeft = Vector3f(center);
    auto shift = Vector3f(-radius, -radius, -radius);
    bottomLeft.add(shift);

    auto topRight = Vector3f(center);
    shift = Vector3f(radius, radius, radius);
    topRight.add(shift);

    return BoundingBox(bottomLeft, topRight);
  }

  HitRecord* buildHitRecord(float t, const Ray& ray) const;

 public:
  Cylinder(Material* material);
  Cylinder(Material* material, float radius);
  virtual HitRecord* intersect(const Ray& ray) const;

  const BoundingBox& getBoundingBox() const { return aabb; }
  virtual std::vector<IntervalBoundary> getIntervalBoundaries(const Ray& ray) const;
};
#endif
