#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

#include "../hitRecord.h"
#include "../ray.h"

class Intersectable {
 public:
  virtual HitRecord* intersect(const Ray&) const = 0;
};
#endif
