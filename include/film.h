#include "spectrum.h"
#include <vector>

#ifndef FILM_H
#define FILM_H

// Boxfilter-film
class Film {
    int access(int, int);

  public:
    int width;
    int height;
    std::vector<Spectrum*>* measurements;
    std::vector<int>* sampleCounts;

    Film(int width, int height);
    void addSample(int x, int y, Spectrum* s);
    std::vector<Spectrum*>* normalMeasurements();
};

#endif
