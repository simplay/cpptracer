#include "image.h"
#include <logger.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <iostream>
#include <sstream>

Image::Image(int width, int height, const std::vector<Spectrum>& values, std::string filename)
    : width(width), height(height), values(values), filename(filename) {}

void Image::print() {
  std::ostringstream oss;
  oss << "Printing " << width << " x " << height << " image... ";

  int x;
  int y;
  int r;
  int g;
  int b;

  FILE* f;
  int filesize = 54 + 3 * width * height;

  unsigned char* img = (unsigned char*)malloc(3 * width * height);
  memset(img, 0, 3 * width * height);

  for (int colIdx = 0; colIdx < width; colIdx++) {
    for (int rowIdx = 0; rowIdx < height; rowIdx++) {
      x = colIdx;
      y = rowIdx;

      const Spectrum& s = values.at(colIdx + rowIdx * width);

      r = s.r * 255;
      g = s.g * 255;
      b = s.b * 255;

      if (r > 255) {
        r = 255;
      }
      if (g > 255) {
        g = 255;
      }
      if (b > 255) {
        b = 255;
      }

      img[(x + y * width) * 3 + 2] = (unsigned char)(r);
      img[(x + y * width) * 3 + 1] = (unsigned char)(g);
      img[(x + y * width) * 3 + 0] = (unsigned char)(b);
    }
  }

  unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
  unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
  unsigned char bmppad[3] = {0, 0, 0};

  bmpfileheader[2] = (unsigned char)(filesize);
  bmpfileheader[3] = (unsigned char)(filesize >> 8);
  bmpfileheader[4] = (unsigned char)(filesize >> 16);
  bmpfileheader[5] = (unsigned char)(filesize >> 24);

  bmpinfoheader[4] = (unsigned char)(width);
  bmpinfoheader[5] = (unsigned char)(width >> 8);
  bmpinfoheader[6] = (unsigned char)(width >> 16);
  bmpinfoheader[7] = (unsigned char)(width >> 24);
  bmpinfoheader[8] = (unsigned char)(height);
  bmpinfoheader[9] = (unsigned char)(height >> 8);
  bmpinfoheader[10] = (unsigned char)(height >> 16);
  bmpinfoheader[11] = (unsigned char)(height >> 24);

  f = fopen(filename.c_str(), "wb");
  fwrite(bmpfileheader, 1, 14, f);
  fwrite(bmpinfoheader, 1, 40, f);
  for (int i = 0; i < height; i++) {
    fwrite(img + (width * (height - i - 1) * 3), 3, width, f);
    fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, f);
  }

  free(img);
  fclose(f);

  oss << "Done" << std::endl;
  oss << "Saved image '" << filename << "'" << std::endl;

  Logger().log(oss.str());
}
