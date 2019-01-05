#include "film.h"
#include "spectrum.h"

Film::Film(int width, int height) {
  _width = width;
  _height = height;
  Spectrum m[width * height];

  // TOOD: remove these dummy values later
  for (int i = 0; i < _width; i++) {
    for (int j = 0; j < _height; j++) {
      float r = ((float) i / _width);
      float g = ((float) j / _height);
      float shift = ((float)(i + j)) / (_width + _height);
      float b = (1 - shift);
      m[i * width + j] = Spectrum(r, g, b);
    }
  }
  _measurements = m;
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
