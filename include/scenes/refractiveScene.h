#include "scene.h"

#ifndef REFRACTIVE_TEST_H
#define REFRACTIVE_TEST_H
class RefractiveTest : public Scene {
  public:
    RefractiveTest(int width, int height);
    void buildCamera();
    void buildLights();
    void buildIntersectables();
    void buildIntegrator();
    std::string filename() {
      return "refractive_test.bmp";
    }
};
#endif
