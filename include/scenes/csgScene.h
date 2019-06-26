#ifndef CSG_SCENE_H
#define CSG_SCENE_H

#include "scene.h"

class CsgScene : public Scene {
  public:
    CsgScene(int width, int height);
    void buildCamera();
    void buildLights();
    void buildIntersectables();
    void buildIntegrator();
    std::string filename() { return "csg_scene.bmp"; }
};
#endif
