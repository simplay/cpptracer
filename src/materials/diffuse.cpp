#include "materials/diffuse.h"
#include <math.h>

// TODO(panmari): Change constructor to expect a const ref. This is currently a memory leak.
Diffuse::Diffuse(const Spectrum* emission) : emission(*emission) {
  this->emission.scale(1.0 / M_PI);
}

Spectrum Diffuse::evaluateBrdf(HitRecord*, Vector3f*, Vector3f*) const { return emission; }

Spectrum Diffuse::evaluateEmission(HitRecord*, Vector3f*) const { return Spectrum(); }

bool Diffuse::hasSpecularReflection() const { return false; }

bool Diffuse::hasSpecularRefraction() const { return false; }

bool Diffuse::castsShadows() const { return true; }

ShadingSample Diffuse::evaluateSpecularReflection(HitRecord* hitRecord) const {
  return ShadingSample();
}

ShadingSample Diffuse::evaluateSpecularRefraction(HitRecord* hitRecord) const {
  return ShadingSample();
}
