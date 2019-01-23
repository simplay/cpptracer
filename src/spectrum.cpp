#include <cmath>
#include "spectrum.h"

Spectrum::Spectrum()
  : r(0), g(0), b(0) {}

Spectrum::Spectrum(float r, float g, float b)
  : r(r), g(g), b(b) {}

Spectrum::Spectrum(float v)
  : r(v), g(v), b(v) {}

Spectrum::Spectrum(Spectrum* s) {
  r = s->r;
  g = s->g;
  b = s->b;
}

void Spectrum::scale(float factor) {
  r *= factor;
  g *= factor;
  b *= factor;
}

void Spectrum::add(Spectrum* other) {
  r += other->r;
  g += other->g;
  b += other->b;
}

void Spectrum::mult(Spectrum* other) {
  r *= other->r;
  g *= other->g;
  b *= other->b;
}
