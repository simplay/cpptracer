#include "materials/pointLightMaterial.h"

// TODO(panmari): Change constructor to only allow const ref. Currently, this is a memory leak.
PointLightMaterial::PointLightMaterial(Spectrum* emission) : emission(*emission) {}

Spectrum PointLightMaterial::evaluateBrdf(HitRecord*, Vector3f*, Vector3f*) const {
  return Spectrum();
}

Spectrum PointLightMaterial::evaluateEmission(HitRecord*, Vector3f*) const { return emission; }

bool PointLightMaterial::hasSpecularReflection() const { return false; }

bool PointLightMaterial::hasSpecularRefraction() const { return false; }

bool PointLightMaterial::castsShadows() const { return false; }

ShadingSample PointLightMaterial::evaluateSpecularReflection(HitRecord* hitRecord) const {
  return ShadingSample();
}

ShadingSample PointLightMaterial::evaluateSpecularRefraction(HitRecord* hitRecord) const {
  return ShadingSample();
}
