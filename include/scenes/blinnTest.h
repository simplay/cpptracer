#include "scene.h"

#ifndef BLINN_TEST_H
#define BLINN_TEST_H
class BlinnTest : public Scene {
  public:
    BlinnTest(int width, int height);
    void buildLights();
    void buildIntersectables();
};
#endif
