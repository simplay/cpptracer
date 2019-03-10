#include "scene.h"

#ifndef MESH_TEST_H
#define MESH_TEST_H
class MeshTest : public Scene {
 public:
  MeshTest(int width, int height);
  void buildCamera();
  void buildLights();
  void buildIntersectables();
  void buildIntegrator();
  void buildSampler();
  std::string filename() { return "mesh_test.bmp"; }
};
#endif
