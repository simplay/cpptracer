#ifndef FILM_H
#define FILM_H

#include <vector>
#include "spectrum.h"

// Boxfilter-film
class Film {
  int access(int, int);

 public:
  int width;
  int height;
  std::vector<Spectrum> measurements;
  std::vector<int> sampleCounts;

  Film(int width, int height);
  void addSample(float x, float y, const Spectrum& s);
  // Returns a copy of measurements normalized by sample counts.
  std::vector<Spectrum> normalMeasurements();
};
#endif
