#include "spectrum.h"
#include <vector>

#ifndef FILM_H
#define FILM_H

// Boxfilter-film
class Film {
  int _width;
  int _height;
  // Spectrum* _measurements;

  int access(int, int);

  public:
    std::vector<Spectrum*>* measurements;
    std::vector<int>* sampleCounts;

    Film();
    Film(int width, int height);
    void addSample(int x, int y, Spectrum* s);
    int width();
    int height();
    std::vector<Spectrum*>* normalMeasurements();
};

#endif
