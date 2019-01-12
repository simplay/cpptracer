#include "hitRecord.h"
#include "ray.h"

#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H
class Intersectable {
  virtual HitRecord* intersect(Ray*) = 0;
};
#endif
