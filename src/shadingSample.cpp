#include "shadingSample.h"

ShadingSample::~ShadingSample() {
  delete brdf;
  delete emission;
  delete w;
}

ShadingSample::ShadingSample(Spectrum* brdf, Spectrum* emission, Vector3f* w, bool isSpecular,
                             float p)
    : brdf(brdf), emission(emission), w(w), isSpecular(isSpecular), isValid(true), p(p) {}

ShadingSample::ShadingSample() : isValid(false) {}
