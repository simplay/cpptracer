#ifndef RENDER_H
#define RENDER_H

#include <renderTask.h>
#include <vector>
#include "scenes/scene.h"

class Renderer {
 private:
  void computeContribution(int, RenderTask*, std::vector<int>*);

 public:
  Scene* scene;
  const bool printProgress;
  Renderer(Scene* scene);
  Renderer(Scene* scene, bool printProgress);
  void render(int threadCount, int spp);
};
#endif
