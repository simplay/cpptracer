#ifndef TRIANGLE_TEST_H
#define TRIANGLE_TEST_H

#include "scene.h"

class TriangleTest : public Scene {
 public:
  TriangleTest(int width, int height);
  void buildLights();
  void buildIntersectables();
  void buildIntegrator();

  std::string filename() { return "triangle_test.bmp"; }
};
#endif
