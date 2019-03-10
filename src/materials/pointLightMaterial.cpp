#include "materials/pointLightMaterial.h"

// TODO(panmari): Change constructor to only allow const ref. Currently, this is a memory leak.
PointLightMaterial::PointLightMaterial(Spectrum* emission): emission(*emission) {}

Spectrum* PointLightMaterial::evaluateBrdf(HitRecord* , Vector3f* , Vector3f* ) {
  return new Spectrum();
}

Spectrum* PointLightMaterial::evaluateEmission(HitRecord*, Vector3f*) {
  return new Spectrum(emission);
}

bool PointLightMaterial::hasSpecularReflection() {
  return false;
}

bool PointLightMaterial::hasSpecularRefraction() {
  return false;
}

bool PointLightMaterial::castsShadows() {
  return false;
}

ShadingSample* PointLightMaterial::evaluateSpecularReflection(HitRecord* hitRecord) {
  return new ShadingSample();
}

ShadingSample* PointLightMaterial::evaluateSpecularRefraction(HitRecord* hitRecord) {
  return new ShadingSample();
}
