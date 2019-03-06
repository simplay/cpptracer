#include "intersectable.h"
#include "../math/vector3f.h"
#include "../hitRecord.h"
#include "../ray.h"

class Material;

#ifndef SPHERE_H
#define SPHERE_H
class Sphere : public Intersectable {
  public:
    Material* material;
    const Vector3f center;
    const float radius;

    Sphere(Material*, Vector3f, float);

    virtual HitRecord* intersect(Ray* ray) const;
};
#endif
