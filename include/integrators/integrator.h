#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "../ray.h"
#include "../scenes/scene.h"
#include "../spectrum.h"

class Integrator {
 public:
  virtual Spectrum* integrate(const Ray&) = 0;
};
#endif
