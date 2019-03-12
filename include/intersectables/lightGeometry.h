#ifndef LIGHT_GEOMETRY_H
#define LIGHT_GEOMETRY_H

#include "../hitRecord.h"
#include "intersectable.h"

class LightGeometry : public Intersectable {
 public:
  virtual HitRecord* sample() const = 0;
};
#endif
