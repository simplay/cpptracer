#ifndef CAMERA_TEST_H
#define CAMERA_TEST_H

#include "scene.h"

class CameraTest : public Scene {
 public:
  CameraTest(int width, int height);
  void buildLights();
  void buildIntersectables();
  std::string filename() { return "camera_test.bmp"; }
};
#endif
