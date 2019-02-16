#include "spectrum.h"
#include "math/point3f.h"

#ifndef SHADING_SAMPLE_H
#define SHADING_SAMPLE_H

class ShadingSample {

  public:
    Spectrum* brdf;
    Spectrum* emission;

    // sample direction
    Point3f* w;

    /**
     * Tells the integrator whether this is a specular sample. In this case, a
     * cosine factor in the specular BRDF should be omitted in the returned
     * BRDF value, and the integrator should act accordingly.
     */
    bool isSpecular;
    bool isValid;

    /**
     * The (directional) probability density of the sample
     */
    float p;

    ~ShadingSample();
    ShadingSample(Spectrum*, Spectrum*, Point3f*, bool, float);
    ShadingSample();

};

#endif
