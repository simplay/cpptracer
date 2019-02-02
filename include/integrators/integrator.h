#include "../spectrum.h"
#include "../scenes/scene.h"
#include "../ray.h"

#ifndef INTEGRATOR_H
#define INTEGRATOR_H
class Integrator {
  public:
    virtual Spectrum* integrate(Ray*) = 0;
};
#endif
