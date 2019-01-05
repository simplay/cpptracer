#include "film.h"
#include "spectrum.h"
#include <iostream>

Film::Film(int width, int height) {
  _width = width;
  _height = height;
  Spectrum *m = NULL;
  m = (Spectrum*)malloc(sizeof(Spectrum) * _width * _height);
  _measurements = m;

  // TOOD: remove these dummy values later
  for (int i = 0; i < _width; i++) {
    for (int j = 0; j < _height; j++) {
      int x = i;
      int y = (_height - 1) - j;

      float r = ((float) i / (_width));
      float g = ((float) j / (_height));
      float shift = ((float)(i + j)) / (_width + _height);
      float b = (1 - shift);
      Spectrum s = Spectrum(r, g, b);

      addSample(x, y, s);
    }
  }
}

void Film::addSample(int x, int y, Spectrum s) {
  _measurements[x + y * _width] = s;
}

int Film::width() {
  return _width;
}

int Film::height() {
  return _height;
}

Spectrum* Film::measurements() {
  return _measurements;
}
