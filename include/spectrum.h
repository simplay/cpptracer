#include <stdio.h>
#include "math/vector3f.h"

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
    Spectrum(const Vector3f&);

    void scale(float);
    void add(const Spectrum&);
    void mult(const Spectrum&);
    void clamp();
    void log() {
      printf("(%f, %f, %f)\n", r, g, b);
    }
};

#endif
