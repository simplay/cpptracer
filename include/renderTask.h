#ifndef RENDER_TASK_H
#define RENDER_TASK_H

#include <vector>
#include "scenes/scene.h"

class RenderTask {
 public:
  int width;
  int height;
  std::vector<int>* indices;
  Scene* scene;
  int spp;
  RenderTask(int, int, std::vector<int>*, Scene*, int);
};
#endif
