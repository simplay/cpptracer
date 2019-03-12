#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include "spectrum.h"

class Image {
 public:
  int width;
  int height;
  const std::vector<Spectrum> values;
  std::string filename;
  Image(int width, int height, const std::vector<Spectrum>& values, std::string);
  void print();
};
#endif
