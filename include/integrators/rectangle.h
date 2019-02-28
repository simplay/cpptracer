#include "intersectable.h"
#include "plane.h"
#include "../math/point3f.h"
#include "../hitRecord.h"
#include "../ray.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

// Construct a plane given its normal and distance to the origin Note that the
// distance is along the direction that the normal points (meaning that the
// sign of distance matters)
class Rectangle : public Plane {
  public:
    Rectangle(Material*, Point3f*, float);
    HitRecord* intersect(Ray*);
};

#endif
