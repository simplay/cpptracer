#include "spectrum.h"

#ifndef IMAGE_H
#define IMAGE_H

class Image {
  public:
    int width;
    int height;
    Spectrum* values;
    Image(int width, int height, Spectrum* values);
    void print();
};

#endif
