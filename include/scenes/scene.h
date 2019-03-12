#ifndef SCENE_H
#define SCENE_H

#include <string.h>
#include "../camera.h"
#include "../film.h"
#include "../intersectables/intersectableList.h"
#include "../lights/pointLight.h"
#include "../samplers/sampler.h"

class Integrator;

class Scene {
 public:
  Film* film;
  Camera* camera;
  std::vector<PointLight*>* lightList;
  IntersectableList* intersectableList;
  Integrator* integrator;
  Sampler* sampler;

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
  virtual void buildSampler();
};
#endif
