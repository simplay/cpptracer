#ifndef DEBUG_INTEGRATOR_H
#define DEBUG_INTEGRATOR_H

#include "../ray.h"
#include "../scenes/scene.h"
#include "../spectrum.h"
#include "integrator.h"

class DebugIntegrator : public Integrator {
 private:
  Scene* scene;
  bool showBinary;

 public:
  DebugIntegrator(Scene*);
  DebugIntegrator(Scene*, bool showBinary);
  Spectrum integrate(const Ray&) const override;
};
#endif
