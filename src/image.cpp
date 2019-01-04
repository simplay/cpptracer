#include "image.h"
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <iostream>

Image::Image() {
  Image(100, 100);
}
Image::Image(int width, int height) {
  _width = width;
  _height = height;
}

void Image::print() {
  std::cout << "Printing " << _width << " x " << _height << " image" << std::endl;

  int x;
  int y;
  int r;
  int g;
  int b;

  FILE *f;
  unsigned char *img = NULL;
  int filesize = 54 + 3 * _width * _height;

  img = (unsigned char *)malloc(3 * _width * _height);
  memset(img, 0, 3 * _width * _height);

  for (int i = 0; i < _width; i++) {
    for (int j = 0; j < _height; j++) {
      x = i;
      y = (_height - 1) - j;
      r = ((float) i / _width) * 255;
      g = ((float) j / _height) * 255;
      float foo = ((float)(i + j)) / (_width + _height);
      b = (1 - foo) * 255;
      if (r > 255)
        r = 255;
      if (g > 255)
        g = 255;
      if (b > 255)
        b = 255;
      img[(x + y * _width) * 3 + 2] = (unsigned char)(r);
      img[(x + y * _width) * 3 + 1] = (unsigned char)(g);
      img[(x + y * _width) * 3 + 0] = (unsigned char)(b);
    }
  }

  unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
  unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
  unsigned char bmppad[3] = {0, 0, 0};

  bmpfileheader[2] = (unsigned char)(filesize);
  bmpfileheader[3] = (unsigned char)(filesize >> 8);
  bmpfileheader[4] = (unsigned char)(filesize >> 16);
  bmpfileheader[5] = (unsigned char)(filesize >> 24);

  bmpinfoheader[4] = (unsigned char)(_width);
  bmpinfoheader[5] = (unsigned char)(_width >> 8);
  bmpinfoheader[6] = (unsigned char)(_width >> 16);
  bmpinfoheader[7] = (unsigned char)(_width >> 24);
  bmpinfoheader[8] = (unsigned char)(_height);
  bmpinfoheader[9] = (unsigned char)(_height >> 8);
  bmpinfoheader[10] = (unsigned char)(_height >> 16);
  bmpinfoheader[11] = (unsigned char)(_height >> 24);

  f = fopen("img.bmp", "wb");
  fwrite(bmpfileheader, 1, 14, f);
  fwrite(bmpinfoheader, 1, 40, f);
  for (int i = 0; i < _height; i++) {
    fwrite(img + (_width * (_height - i - 1) * 3), 3, _width, f);
    fwrite(bmppad, 1, (4 - (_width * 3) % 4) % 4, f);
  }

  free(img);
  fclose(f);

  std::cout << "Saved image 'img.bmp'" << std::endl;
}
