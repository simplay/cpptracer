#ifndef REFRACTIVE_TEST_H
#define REFRACTIVE_TEST_H

#include "scene.h"

class RefractiveTest : public Scene {
 public:
  RefractiveTest(int width, int height);
  void buildCamera();
  void buildLights();
  void buildIntersectables();
  void buildIntegrator();
  void buildSampler();
  std::string filename() { return "refractive_test.bmp"; }
};
#endif
