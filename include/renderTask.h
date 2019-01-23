#include <vector>
#include "scenes/scene.h"

#ifndef RENDER_TASK_H
#define RENDER_TASK_H
class RenderTask {
  public:
    int width;
    int height;
    std::vector<int>* indices;
    Scene* scene;
    RenderTask(int, int, std::vector<int>*, Scene*);
};
#endif
