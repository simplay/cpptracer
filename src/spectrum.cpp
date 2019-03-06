#include <algorithm>
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

Spectrum::Spectrum(Vector3f* s) {
  r = s->x;
  g = s->y;
  b = s->z;
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

void Spectrum::clamp() {
  if (r > 1) {
    r = 1.0;
  }

  if (g > 1) {
    g = 1.0;
  }

  if (b > 1) {
    b = 1.0;
  }
}
