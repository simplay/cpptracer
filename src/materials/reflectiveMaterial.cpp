#include <math.h>
#include "materials/reflectiveMaterial.h"

ReflectiveMaterial::ReflectiveMaterial(): ks(new Spectrum(1, 1, 1)) {}
ReflectiveMaterial::ReflectiveMaterial(Spectrum* ks): ks(ks) {}

Spectrum* ReflectiveMaterial::evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn) {
  return new Spectrum(1);
}

Spectrum* ReflectiveMaterial::evaluateEmission(HitRecord*, Vector3f*) {
  return new Spectrum();
}

bool ReflectiveMaterial::hasSpecularReflection() {
  return true;
}

bool ReflectiveMaterial::hasSpecularRefraction() {
  return false;
}

bool ReflectiveMaterial::castsShadows() {
  return true;
}

ShadingSample* ReflectiveMaterial::evaluateSpecularReflection(HitRecord* hitRecord) {
  auto reflectedDir = hitRecord->wIn->invReflected(hitRecord->normal);
  ShadingSample* sample = new ShadingSample(
    new Spectrum(ks),
    new Spectrum(),
    reflectedDir,
    true,
    1
  );
  return sample;
}

ShadingSample* ReflectiveMaterial::evaluateSpecularRefraction(HitRecord* hitRecord) {
  return new ShadingSample();
}
