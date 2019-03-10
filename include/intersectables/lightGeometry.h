#include "../hitRecord.h"
#include "intersectable.h"

#ifndef LIGHT_GEOMETRY_H
#define LIGHT_GEOMETRY_H

class LightGeometry : public Intersectable {
 public:
  virtual HitRecord* sample() const = 0;
};
#endif
