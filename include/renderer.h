#include "scenes/scene.h"
#include <renderTask.h>
#include <vector>

#ifndef RENDER_H
#define RENDER_H
class Renderer {
  private:
    void computeContribution(int, RenderTask*, std::vector<int>*);

  public:
    Scene* scene;
    Renderer(Scene* scene);
    void render(int threadCount, int spp);
};
#endif
