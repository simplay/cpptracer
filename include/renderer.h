#include "scenes/scene.h"
#include <renderTask.h>

#ifndef RENDER_H
#define RENDER_H
class Renderer {
  private:
    void computeContribution(RenderTask*);

  public:
    Scene* scene;
    Renderer(Scene* scene);
    void render(int threadCount, int spp);
};
#endif
