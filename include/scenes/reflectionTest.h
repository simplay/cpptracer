#ifndef REFLECTION_TEST_H
#define REFLECTION_TEST_H

#include "scene.h"

class ReflectionTest : public Scene {
 public:
  ReflectionTest(int width, int height);
  void buildLights();
  void buildIntersectables();
  void buildIntegrator();
  void buildSampler();
  std::string filename() { return "reflection_test.bmp"; }
};
#endif
