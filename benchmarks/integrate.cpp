#include <benchmark/benchmark.h>
#include "integrators/whittedIntegrator.h"
#include "intersectables/geometries/sphere.h"
#include "materials/diffuse.h"
#include "materials/reflectiveMaterial.h"
#include "materials/refractiveMaterial.h"

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
  Diffuse diffuse = Diffuse(new Spectrum(0.0, 0.5, 0.5));
  RefractiveMaterial refractive = RefractiveMaterial(1.1);
  ReflectiveMaterial reflective = ReflectiveMaterial();
  IntersectableList* intersectableList = new IntersectableList();
  intersectableList->put(new Sphere(&diffuse, Vector3f(0.0, 0.0, 0.0), 0.5));
  intersectableList->put(new Sphere(&refractive, Vector3f(0.0, 0.8, 0.0), 0.5));
  intersectableList->put(new Sphere(&reflective, Vector3f(0.8, 0.0, 0.0), 0.5));

  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(Vector3f(0.5, 0.5, 2.0), new Spectrum(1.0)));

  auto integrator = WhittedIntegrator(intersectableList, lightList);

  auto rays = MakeRays();

  for (auto _ : state) {
    for (const auto& r : rays) {
      benchmark::DoNotOptimize(integrator.integrate(r));
    }
  }
}
BENCHMARK(BM_WhittedIntegrator);
}  // namespace
