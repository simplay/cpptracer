#ifndef LIGHT_GEOMETRY_H
#define LIGHT_GEOMETRY_H

#include "hitRecord.h"
#include "intersectables/accelerator/boundingBox.h"
#include "intersectables/intersectable.h"

class LightGeometry : public Intersectable {
 private:
  BoundingBox aabb = BoundingBox(Vector3f(0, 0, 0), Vector3f(0, 0, 0));

 public:
  virtual HitRecord* sample() const = 0;
  const BoundingBox& getBoundingBox() const { return aabb; }
};
#endif
