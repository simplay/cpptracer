#include "spectrum.h"
#include <cmath>

Spectrum::Spectrum() {
  _r = 0;
  _g = 0;
  _b = 0;
}

Spectrum::Spectrum(float r, float g, float b) {
  _r = r;
  _g = g;
  _b = b;
}

float Spectrum::r() {
  return _r;
}

float Spectrum::g() {
  return _g;
}

float Spectrum::b() {
  return _b;
}
