#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "intersectables/geometries/lightGeometry.h"
#include "spectrum.h"

class Material;

class PointLight : public LightGeometry {
 private:
  const Vector3f position;
  Material* material;

 public:
  PointLight(Vector3f, Spectrum*);
  virtual HitRecord* sample() const;
  virtual HitRecord* intersect(const Ray&) const;
};
#endif
