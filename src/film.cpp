#include "film.h"
#include "spectrum.h"
#include <iostream>

Film::Film() {}

Film::Film(int width, int height) {
  _width = width;
  _height = height;
  Spectrum *m = NULL;
  m = (Spectrum*)malloc(sizeof(Spectrum) * _width * _height);
  _measurements = m;

  int *s = NULL;
  s = (int*)malloc(sizeof(int) * _width * _height);
  _sampleCounts = s;

  for (int k = 0; k < width; k++) {
    for (int l = 0; l < height; l++) {
      _sampleCounts[k + l * _width] = 0;
    }
  }
}

void Film::addSample(int x, int y, Spectrum* s) {
  _sampleCounts[x + y * _width]++;
  _measurements[x + y * _width] = s;
}

int Film::width() {
  return _width;
}

int Film::height() {
  return _height;
}

Spectrum* Film::measurements() {
  for (int k = 0; k < _width; k++) {
    for (int l = 0; l < _height; l++) {
      int f = _sampleCounts[k + l * _width];
      Spectrum s = _measurements[k + l * _width];
      if (f > 0) {
        s.scale(1.0 / (float) f);
      }
    }
  }

  return _measurements;
}
