#include "shadingSample.h"

ShadingSample::ShadingSample(const Spectrum brdf, const Spectrum emission, const Vector3f w,
                             bool isSpecular, float p)
    : brdf(brdf), emission(emission), w(w), isSpecular(isSpecular), isValid(true), p(p) {}

ShadingSample::ShadingSample() : isSpecular(false), isValid(false), p(0) {}
