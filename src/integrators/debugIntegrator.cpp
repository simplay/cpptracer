#include <integrators/debugIntegrator.h>

DebugIntegrator::DebugIntegrator(Scene* scene) : scene(scene), showBinary(false) {}
DebugIntegrator::DebugIntegrator(Scene* scene, bool showBinary)
    : scene(scene), showBinary(showBinary) {}

Spectrum DebugIntegrator::integrate(const Ray& ray) const {
  HitRecord* hitRecord = scene->intersectableList->intersect(ray);
  if (!hitRecord->isValid()) {
    return Spectrum();
  }

  if (hitRecord->t > 0) {
    if (showBinary) {
      return Spectrum(0, 1, 0);
    } else {
      auto n = Vector3f(*hitRecord->normal);
      n.scale(0.5);
      n.add(Vector3f(1, 1, 1));
      n.normalize();

      // Uncomment this in case we want to dumb the normals
      // std::cout << "(" << hitRecord->i << ", " << hitRecord->j << ") => ";
      // n->log();
      return Spectrum(n);
    }
  } else {
    return Spectrum(1, 0, 0);
  }
}
