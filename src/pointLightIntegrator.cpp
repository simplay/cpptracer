#include "pointLightIntegrator.h"

PointLightIntegrator::PointLightIntegrator(Scene* scene): scene(scene) {}

Spectrum* PointLightIntegrator::integrate(Ray* ray) {
  HitRecord* hitRecord = scene->intersectableList->intersect(ray);
  if (!hitRecord->isValid()) {
    return new Spectrum();
  }

  if (hitRecord->t > 0.0) {
    return new Spectrum(1, 0, 0);
  } else {
    return new Spectrum(0, 1, 0);
  }
}
