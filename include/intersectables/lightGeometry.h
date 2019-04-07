#ifndef LIGHT_GEOMETRY_H
#define LIGHT_GEOMETRY_H

#include "../hitRecord.h"
#include "boundingBox.h"
#include "intersectable.h"

class LightGeometry : public Intersectable {
 public:
  virtual HitRecord* sample() const = 0;
  BoundingBox getBoundingBox() const {
    BoundingBox foo(Vector3f(0, 0, 0), Vector3f(0, 0, 0));
    return foo;
  }
};
#endif
