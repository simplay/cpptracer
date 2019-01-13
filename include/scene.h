#include "film.h"
#include "camera.h"
#include "pointLight.h"
#include "intersectableList.h"
class PointLightIntegrator;

#ifndef SCENE_H
#define SCENE_H
class Scene {
  public:
    Film* film;
    Camera* camera;
    std::vector<PointLight*>* lightList;
    IntersectableList* intersectableList;
    Scene(int widht, int height);
    PointLightIntegrator* integrator;
};
#endif
