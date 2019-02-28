#include "scene.h"

#ifndef CUBE_TEST_H
#define CUBE_TEST_H
class CubeTest : public Scene {
  public:
    CubeTest(int width, int height);
    void buildCamera();
    void buildLights();
    void buildIntersectables();
    void buildIntegrator();
    std::string filename() {
      return "cube_test.bmp";
    }
};
#endif
