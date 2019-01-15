#include "spectrum.h"

#ifndef FILM_H
#define FILM_H

// Boxfilter-film
class Film {
  int _width;
  int _height;
  Spectrum* _measurements;
  int* _sampleCounts;

  public:

  Film();
  Film(int width, int height);
  void addSample(int x, int y, Spectrum* s);
  int width();
  int height();
  Spectrum* measurements();
};

#endif
