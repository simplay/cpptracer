#include "materials/reflectiveMaterial.h"
#include <math.h>

ReflectiveMaterial::ReflectiveMaterial() : ks(1, 1, 1) {}
// TODO(panmari): Change constructor to expect a const ref. This is currently a memory leak.
ReflectiveMaterial::ReflectiveMaterial(Spectrum* ks) : ks(*ks) {}

Spectrum ReflectiveMaterial::evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut,
                                          Vector3f* wIn) const {
  return Spectrum(1);
}

Spectrum ReflectiveMaterial::evaluateEmission(HitRecord*, Vector3f*) const { return Spectrum(); }

bool ReflectiveMaterial::hasSpecularReflection() const { return true; }

bool ReflectiveMaterial::hasSpecularRefraction() const { return false; }

bool ReflectiveMaterial::castsShadows() const { return true; }

ShadingSample ReflectiveMaterial::evaluateSpecularReflection(HitRecord* hitRecord) const {
  auto reflectedDir = hitRecord->wIn->invReflected(*hitRecord->normal);
  return ShadingSample(Spectrum(ks), Spectrum(), *reflectedDir, true, 1);
}

ShadingSample ReflectiveMaterial::evaluateSpecularRefraction(HitRecord* hitRecord) const {
  return ShadingSample();
}
