#include "intersectable.h"
#include "plane.h"
#include "../math/point3f.h"
#include "../hitRecord.h"
#include "../ray.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public Plane {
  public:
    Rectangle(Material*, Point3f*, float);
    HitRecord* intersect(Ray*);
};

#endif
