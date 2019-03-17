#ifndef SHADING_SAMPLE_H
#define SHADING_SAMPLE_H

#include "math/vector3f.h"
#include "spectrum.h"

class ShadingSample {
 public:
  const Spectrum brdf;
  const Spectrum emission;

  // sample direction
  const Vector3f w;

  /**
   * Tells the integrator whether this is a specular sample. In this case, a
   * cosine factor in the specular BRDF should be omitted in the returned
   * BRDF value, and the integrator should act accordingly.
   */
  const bool isSpecular;
  const bool isValid;

  /**
   * The (directional) probability density of the sample
   */
  const float p;

  ShadingSample(Spectrum, Spectrum, Vector3f, bool, float);
  ShadingSample();
};
#endif
