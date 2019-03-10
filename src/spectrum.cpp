#include <algorithm>
#include <cmath>
#include "spectrum.h"

Spectrum::Spectrum()
  : r(0), g(0), b(0) {}

Spectrum::Spectrum(float r, float g, float b)
  : r(r), g(g), b(b) {}

Spectrum::Spectrum(float v)
  : r(v), g(v), b(v) {}

Spectrum::Spectrum(const Vector3f& v) {
  r = v.x;
  g = v.y;
  b = v.z;
}

void Spectrum::scale(float factor) {
  r *= factor;
  g *= factor;
  b *= factor;
}

void Spectrum::add(const Spectrum& other) {
  r += other.r;
  g += other.g;
  b += other.b;
}

void Spectrum::mult(const Spectrum& other) {
  r *= other.r;
  g *= other.g;
  b *= other.b;
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
