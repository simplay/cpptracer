#include "shadingSample.h"

ShadingSample::ShadingSample(Spectrum* brdf, Spectrum* emission, Point3f* w, bool isSpecular, float p)
  : brdf(brdf), emission(emission), w(w), isSpecular(isSpecular), p(p), isValid(true) {}

ShadingSample::ShadingSample()
  : isValid(false) {}
