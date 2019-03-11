#include "renderTask.h"

RenderTask::RenderTask(int width, int height, std::vector<int>* indices, Scene* scene, int spp)
    : width(width), height(height), indices(indices), scene(scene), spp(spp) {}
