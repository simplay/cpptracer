#ifndef EXPLOSION_TEST_H
#define EXPLOSION_TEST_H

#include "scene.h"

class ExplosionTest : public Scene {
 public:
  ExplosionTest(int width, int height);
  void buildLights();
  void buildIntersectables();
  std::string filename() { return "explosion_test.bmp"; }
};
#endif
