#include "pointLight.h"
#include "pointLightMaterial.h"
#include "material.h"

PointLight::PointLight(Point3f* position, Spectrum* emission)
  : position(position), material((Material *) new PointLightMaterial(emission))
{}

HitRecord* PointLight::sample() {
  return new HitRecord(
      new Point3f(position),
      material
  );
}
