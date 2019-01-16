#include "film.h"
#include "spectrum.h"
#include <iostream>

Film::Film() {}

Film::Film(int width, int height) {
  _width = width;
  _height = height;

  measurements = new std::vector<Spectrum*>(width * height);
  sampleCounts = new std::vector<int>(width * height);

  for (int k = 0; k < height; k++) {
    for (int l = 0; l < width; l++) {
      sampleCounts->at(access(k, l)) = 0;
    }
  }
}

void Film::addSample(int x, int y, Spectrum* s) {
  // std::cout << "addSample: " << x << " " << y << std::endl;
  // std::cout << "foo" << std::endl;
  // sampleCounts->at(access(x, y))++;
  measurements->at(access(x, y)) = s;
}

int Film::access(int x, int y) {
  return x + y * _height;
}

int Film::width() {
  return _width;
}

int Film::height() {
  return _height;
}

std::vector<Spectrum*>* Film::normalMeasurements() {
  for (int k = 0; k < _height; k++) {
    for (int l = 0; l < _width; l++) {
      int f = 1; sampleCounts->at(access(k, l));
      Spectrum* s = measurements->at(access(k, l));
      if (f > 0) {
        s->scale(1.0 / (float) f);
      }
    }
  }

  return measurements;
}
