#include "scene.h"

#ifndef TRIANGLE_TEST_H
#define TRIANGLE_TEST_H
class TriangleTest : public Scene {
  public:
    TriangleTest(int width, int height);
    void buildLights();
    void buildIntersectables();
    std::string filename() {
      return "triangle_test.bmp";
    }
};
#endif
