#include <math.h>
#include "reflectiveMaterial.h"

ReflectiveMaterial::ReflectiveMaterial(): ks(new Spectrum(1, 1, 1)) {}
ReflectiveMaterial::ReflectiveMaterial(Spectrum* ks): ks(ks) {}

Spectrum* ReflectiveMaterial::evaluateBrdf(HitRecord* hitRecord, Point3f* wOut, Point3f* wIn) {
  return new Spectrum();
}

Spectrum* ReflectiveMaterial::evaluateEmission(HitRecord*, Point3f*) {
  return new Spectrum(1, 1, 1);
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
  // compute reflection direction
  float cosThetaI = hitRecord->normal->dot(hitRecord->wIn);
  Point3f* reflectedDir= new Point3f();
  Point3f wInCopy(hitRecord->wIn);
  wInCopy.negate();
  wInCopy.add(hitRecord->normal);
  wInCopy.scale(2 * cosThetaI);
  reflectedDir->add(&wInCopy);

  ShadingSample* sample = new ShadingSample(
    new Spectrum(ks),
    new Spectrum(),
    reflectedDir,
    true,
    1
  );
  return sample;
}
