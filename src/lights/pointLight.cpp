#include "pointLight.h"
#include "pointLightMaterial.h"
#include "../materials/material.h"

PointLight::PointLight(Vector3f* position, Spectrum* emission)
  : position(position), material((Material *) new PointLightMaterial(emission))
{}

HitRecord* PointLight::sample() const {
  return new HitRecord(
      new Vector3f(position),
      material
  );
}

HitRecord* PointLight::intersect(Ray*) const {
  return new HitRecord();
}
