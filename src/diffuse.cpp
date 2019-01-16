#include "diffuse.h"
#include <math.h>

Diffuse::Diffuse(Spectrum* emission): emission(emission) {
  emission->scale(1.0 / M_PI);
}

Spectrum* Diffuse::evaluateBrdf(HitRecord* , Point3f* , Point3f* ) {
  return new Spectrum(emission);
}

Spectrum* Diffuse::evaluateEmission(HitRecord*, Point3f*) {
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
