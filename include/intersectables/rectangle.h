#include "intersectable.h"
#include "plane.h"
#include "../math/vector3f.h"
#include "../hitRecord.h"
#include "../ray.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public Plane {
  public:
    Rectangle(Material*, Vector3f, float);
    HitRecord* intersect(Ray*);
};

#endif
