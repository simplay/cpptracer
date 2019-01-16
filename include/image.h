#include <vector>
#include "spectrum.h"

#ifndef IMAGE_H
#define IMAGE_H

class Image {
  public:
    int width;
    int height;
    std::vector<Spectrum*>* values;
    Image(int width, int height, std::vector<Spectrum*>* values);
    void print();
};

#endif
