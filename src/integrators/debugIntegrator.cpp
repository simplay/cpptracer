#include <debugIntegrator.h>

DebugIntegrator::DebugIntegrator(Scene* scene): scene(scene) {}

Spectrum* DebugIntegrator::integrate(Ray* ray) {
  HitRecord* hitRecord = scene->intersectableList->intersect(ray);
  if (!hitRecord->isValid()) {
    return new Spectrum();
  }

  if (hitRecord->t > 0) {
    return new Spectrum(0, 1, 0);
  } else {
    return new Spectrum(1, 0, 0);
  }
}
