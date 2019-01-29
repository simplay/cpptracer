#include <vector>
#include <string>
#include "spectrum.h"

#ifndef IMAGE_H
#define IMAGE_H

class Image {
  public:
    int width;
    int height;
    std::vector<Spectrum*>* values;
    std::string filename;
    Image(int width, int height, std::vector<Spectrum*>* values, std::string);
    void print();
};

#endif
