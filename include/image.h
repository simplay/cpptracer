#include "spectrum.h"

#ifndef IMAGE_H
#define IMAGE_H

class Image {

  int _width;
  int _height;
  Spectrum * _values;

  public:

  Image(int width, int height, Spectrum* values);
  void print();

};

#endif
