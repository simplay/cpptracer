#include "../hitRecord.h"
#include "../math/vector3f.h"
#include "../ray.h"
#include "intersectable.h"

class Material;

#ifndef SPHERE_H
#define SPHERE_H
class Sphere : public Intersectable {
 private:
  Material* material;
  const Vector3f center;
  const float radius;

 public:
  Sphere(Material*, const Vector3f&, float);
  virtual HitRecord* intersect(Ray* ray) const;
};
#endif
