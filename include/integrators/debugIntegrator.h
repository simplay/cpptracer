#include "integrator.h"
#include "../spectrum.h"
#include "../scenes/scene.h"
#include "../ray.h"

#ifndef DEBUG_INTEGRATOR_H
#define DEBUG_INTEGRATOR_H
class DebugIntegrator : public Integrator {
  private:
    Scene* scene;
    bool showBinary;

  public:
    DebugIntegrator(Scene*);
    DebugIntegrator(Scene*, bool showBinary);
    Spectrum* integrate(Ray*);
};
#endif
