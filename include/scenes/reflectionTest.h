#include "scene.h"

#ifndef REFLECTION_TEST_H
#define REFLECTION_TEST_H
class ReflectionTest : public Scene {
  public:
    ReflectionTest(int width, int height);
    void buildLights();
    void buildIntersectables();
    void buildIntegrator();
    std::string filename() {
      return "reflection_test.bmp";
    }
};
#endif
