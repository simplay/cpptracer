#include <math.h>
#include "materials/diffuse.h"

Diffuse::Diffuse(Spectrum* emission): emission(emission) {
  emission->scale(1.0 / M_PI);
}

Spectrum* Diffuse::evaluateBrdf(HitRecord* , Vector3f* , Vector3f* ) {
  return new Spectrum(emission);
}

Spectrum* Diffuse::evaluateEmission(HitRecord*, Vector3f*) {
  return new Spectrum();
}

bool Diffuse::hasSpecularReflection() {
  return false;
}

bool Diffuse::hasSpecularRefraction() {
  return false;
}

bool Diffuse::castsShadows() {
  return true;
}

ShadingSample* Diffuse::evaluateSpecularReflection(HitRecord* hitRecord) {
  return new ShadingSample();
}

ShadingSample* Diffuse::evaluateSpecularRefraction(HitRecord* hitRecord) {
  return new ShadingSample();
}
