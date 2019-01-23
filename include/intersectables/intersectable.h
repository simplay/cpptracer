#include "../hitRecord.h"
#include "../ray.h"

#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H
class Intersectable {
  public:
    virtual HitRecord* intersect(Ray*) = 0;
};
#endif
