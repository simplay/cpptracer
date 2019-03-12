#ifndef BLINN_TEST_H
#define BLINN_TEST_H

#include "scene.h"

class BlinnTest : public Scene {
 public:
  BlinnTest(int width, int height);
  void buildCamera();
  void buildLights();
  void buildIntersectables();
  void buildIntegrator();
  std::string filename() { return "blinn_test.bmp"; }
};
#endif
