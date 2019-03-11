#include "../ray.h"
#include "../scenes/scene.h"
#include "../spectrum.h"

#ifndef INTEGRATOR_H
#define INTEGRATOR_H
class Integrator {
 public:
  virtual Spectrum* integrate(Ray*) = 0;
};
#endif
