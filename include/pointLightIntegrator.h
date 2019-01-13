#include "spectrum.h"
#include "scene.h"
#include "ray.h"

#ifndef POINT_LIGHT_INTEGRATOR_H
#define POINT_LIGHT_INTEGRATOR_H
class PointLightIntegrator {
  private:
    Scene* scene;

  public:
    PointLightIntegrator(Scene*);
    Spectrum* integrate(Ray*);
};
#endif
