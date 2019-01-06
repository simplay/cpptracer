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
