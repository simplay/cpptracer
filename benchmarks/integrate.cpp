#include <benchmark/benchmark.h>
#include "integrators/whittedIntegrator.h"
#include "intersectables/sphere.h"
#include "materials/diffuse.h"

namespace {
std::vector<Ray> MakeRays() {
  return {
      Ray(new Vector3f(1.0, 1.0, 1.0), new Vector3f(-1, -1, -1)),
      Ray(new Vector3f(-1.0, -1.0, -1.0), new Vector3f(1, 1, 1)),
      Ray(new Vector3f(0.5, 0.5, 1.0), new Vector3f(0, 0, -1)),
      Ray(new Vector3f(0.5, 0.5, -1.0), new Vector3f(0, 0, 1)),
  };
}

static void BM_WhittedIntegrator(benchmark::State& state) {
  Material* diffuse = new Diffuse(new Spectrum(0.0, 0.5, 0.5));
  IntersectableList* intersectableList = new IntersectableList();
  intersectableList->put(new Sphere(diffuse, Vector3f(0.0, 0.0, 0.0), 0.5));

  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(Vector3f(0.5, 0.5, 2.0), new Spectrum(1.0)));

  auto integrator = WhittedIntegrator(intersectableList, lightList);

  auto rays = MakeRays();

  for (auto _ : state) {
    for (auto& r : rays) {
      integrator.integrate(r);
    }
  }
}
BENCHMARK(BM_WhittedIntegrator);
}  // namespace
