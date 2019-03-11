#include <math.h>
#include <iostream>

#include "film.h"
#include "spectrum.h"

Film::Film(int width, int height)
    : width(width), height(height), measurements(width * height), sampleCounts(width * height) {}

// store spectrum in row-first order
void Film::addSample(float rowIdx, float colIdx, const Spectrum& spectrum) {
  int roundedRowIdx = std::round(rowIdx);
  int roundedColIdx = std::round(colIdx);

  if (roundedColIdx >= width) {
    return;
  }

  if (roundedRowIdx >= height) {
    return;
  }

  measurements.at(access(roundedRowIdx, roundedColIdx)).add(spectrum);
  sampleCounts.at(access(roundedRowIdx, roundedColIdx))++;
}

// access values in row-first order
int Film::access(int rowIdx, int colIdx) { return colIdx + rowIdx * width; }

std::vector<Spectrum> Film::normalMeasurements() {
  auto normed = measurements;
  for (int colIdx = 0; colIdx < width; colIdx++) {
    for (int rowIdx = 0; rowIdx < height; rowIdx++) {
      int c = sampleCounts.at(access(rowIdx, colIdx));
      if (c == 0) {
        continue;
      }
      normed.at(access(rowIdx, colIdx)).scale(1.0 / c);
    }
  }

  return normed;
}
