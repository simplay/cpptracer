#include "scene.h"

#ifndef EXPLOSION_TEST_H
#define EXPLOSION_TEST_H
class ExplosionTest : public Scene {
  public:
    ExplosionTest(int width, int height);
    void buildLights();
    void buildIntersectables();
};
#endif

