#include <iostream>
#include "film.h"
#include "spectrum.h"

Film::Film(int width, int height): width(width), height(height) {
  measurements = new std::vector<Spectrum*>(width * height);
  sampleCounts = new std::vector<int>(width * height);

  for (int colIdx = 0; colIdx < width; colIdx++) {
    for (int rowIdx = 0; rowIdx < height; rowIdx++) {
      sampleCounts->at(access(rowIdx, colIdx)) = 0;
    }
  }
}

// store spectrum in row-first order
void Film::addSample(int rowIdx, int colIdx, Spectrum* spectrum) {
  auto v = measurements->at(access(rowIdx, colIdx));
  sampleCounts->at(access(rowIdx, colIdx))++;
  if (v) {
    v->add(spectrum);
    v->clamp();
    measurements->at(access(rowIdx, colIdx)) = v;
  } else {
    measurements->at(access(rowIdx, colIdx)) = spectrum;
  }
}

// access values in row-first order
int Film::access(int rowIdx, int colIdx) {
  return colIdx + rowIdx * width;
}

std::vector<Spectrum*>* Film::normalMeasurements() {
  for (int colIdx = 0; colIdx < width; colIdx++) {
    for (int rowIdx = 0; rowIdx < height; rowIdx++) {
      int f = sampleCounts->at(access(rowIdx, colIdx));
      Spectrum* s = measurements->at(access(rowIdx, colIdx));
      if (f > 0) {
        s->scale(1.0 / f);
      }
    }
  }

  return measurements;
}
