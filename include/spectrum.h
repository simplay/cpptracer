#include "point3f.h"

#ifndef SPECTRUM_H
#define SPECTRUM_H

/**
 * Float valued point with 3 coordinates.
 */
class Spectrum {

  public:
    float r;
    float g;
    float b;

    Spectrum();
    Spectrum(float, float, float);
    Spectrum(float);
    Spectrum(Spectrum*);

    void scale(float);
    void add(Spectrum*);
    void mult(Spectrum*);
};

#endif
