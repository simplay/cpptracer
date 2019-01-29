#include <string.h>
#include "../film.h"
#include "../camera.h"
#include "../lights/pointLight.h"
#include "../intersectables/intersectableList.h"
class PointLightIntegrator;

#ifndef SCENE_H
#define SCENE_H
class Scene {
  public:
    Film* film;
    Camera* camera;
    std::vector<PointLight*>* lightList;
    IntersectableList* intersectableList;
    PointLightIntegrator* integrator;
    Scene(int widht, int height);
    void setup();
    virtual std::string filename();

  protected:
    // image width
    int width;

    // image height
    int height;

    virtual void buildFilm();
    virtual void buildCamera();
    virtual void buildLights() = 0;
    virtual void buildIntersectables() = 0;
    virtual void buildIntegrator();
};
#endif
