#include "intersectable.h"
#include "../math/point3f.h"
#include "../hitRecord.h"
#include "../ray.h"

class Material;

#ifndef SPHERE_H
#define SPHERE_H
class Sphere : public Intersectable {
  public:
    Material* material;
    Point3f* center;
    float radius;

    Sphere(Material*, Point3f*, float);

    virtual HitRecord* intersect(Ray* ray);
};
#endif
