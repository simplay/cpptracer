#include <iostream>
#include <debugIntegrator.h>

DebugIntegrator::DebugIntegrator(Scene* scene): scene(scene), showBinary(false) {}
DebugIntegrator::DebugIntegrator(Scene* scene, bool showBinary): scene(scene), showBinary(showBinary) {}

Spectrum* DebugIntegrator::integrate(Ray* ray) {
  HitRecord* hitRecord = scene->intersectableList->intersect(ray);
  if (!hitRecord->isValid()) {
    return new Spectrum();
  }

  if (hitRecord->t > 0) {
    if (showBinary) {
      return new Spectrum(0, 1, 0);
    } else {
      Point3f* n = new Point3f(hitRecord->normal);
      n->scale(0.5);
      n->add(new Point3f(1, 1, 1));
      n->normalize();

      // Uncomment this in case we want to dumb the normals
      // std::cout << "(" << hitRecord->i << ", " << hitRecord->j << ") => ";
      // n->log();
      return new Spectrum(n);
    }
  } else {
    return new Spectrum(1, 0, 0);
  }
}
