#include <benchmark/benchmark.h>
#include <memory>
#include "../intersectables/explosion.h"
#include "../intersectables/meshTriangle.h"
#include "../intersectables/plane.h"
#include "../intersectables/sphere.h"
#include "../intersectables/triangle.h"
#include "../lights/pointLight.h"
#include "../materials/diffuse.h"
#include "../math/vector4f.h"

namespace {

std::vector<Ray> MakeRays() {
  return {
      Ray(new Vector3f(1.0, 1.0, 1.0), new Vector3f(-1, -1, -1)),
      Ray(new Vector3f(-1.0, -1.0, -1.0), new Vector3f(1, 1, 1)),
      Ray(new Vector3f(0.5, 0.5, 1.0), new Vector3f(0, 0, -1)),
      Ray(new Vector3f(0.5, 0.5, -1.0), new Vector3f(0, 0, 1)),
  };
}

static void BM_TriangleIntersect(benchmark::State& state) {
  Diffuse material = Diffuse(new Spectrum(1.0));
  auto triangle = Triangle(1, &material, Vector3f(0.0, 0.0, 0.0), Vector3f(1.0, 0.0, 0.0),
                           Vector3f(0.0, 1.0, 0.0));

  auto rays = MakeRays();

  for (auto _ : state) {
    for (auto& r : rays) {
      std::unique_ptr<HitRecord>(triangle.intersect(&r));
    }
  }
}
BENCHMARK(BM_TriangleIntersect);

static void BM_SphereIntersect(benchmark::State& state) {
  Diffuse material = Diffuse(new Spectrum(1.0));
  auto sphere = Sphere(&material, Vector3f(0.0, 0.0, 0.0), 1);

  auto rays = MakeRays();

  for (auto _ : state) {
    for (auto& r : rays) {
      std::unique_ptr<HitRecord>(sphere.intersect(&r));
    }
  }
}
BENCHMARK(BM_SphereIntersect);

static void BM_ExplosionIntersect(benchmark::State& state) {
  Diffuse material = Diffuse(new Spectrum(1.0));
  auto explosion = Explosion(&material, Vector3f(0.0, 0.0, 0.0), 1);

  auto rays = MakeRays();

  for (auto _ : state) {
    for (auto& r : rays) {
      std::unique_ptr<HitRecord>(explosion.intersect(&r));
    }
  }
}
BENCHMARK(BM_ExplosionIntersect);

static void BM_PlaneIntersect(benchmark::State& state) {
  Diffuse material = Diffuse(new Spectrum(1.0));
  auto plane = Plane(&material, Vector3f(0.0, 0.0, 0.0), 1);

  auto rays = MakeRays();
  for (auto _ : state) {
    for (auto& r : rays) {
      std::unique_ptr<HitRecord>(plane.intersect(&r));
    }
  }
}
BENCHMARK(BM_PlaneIntersect);

static void BM_PointLightIntersect(benchmark::State& state) {
  auto light = PointLight(Vector3f(0.0, 0.0, 0.0), new Spectrum(1.0));

  auto rays = MakeRays();
  for (auto _ : state) {
    for (auto& r : rays) {
      std::unique_ptr<HitRecord>(light.intersect(&r));
    }
  }
}
BENCHMARK(BM_PointLightIntersect);

static void BM_MeshTriangleTntersect(benchmark::State& state) {
  Diffuse material = Diffuse(new Spectrum(1.0));
  auto meshTriangle =
      MeshTriangle(1, &material, Vector3f(0.0, 0.0, 0.0), Vector3f(1.0, 0.0, 0.0),
                   Vector3f(0.0, 1.0, 0.0), Vector3f(1.0, 0.0, 0.0),
                   Vector3f(0.0, 1.0, 0.0), Vector3f(0.0, 0.0, 1.0));

  auto rays = MakeRays();
  for (auto _ : state) {
    for (auto& r : rays) {
      std::unique_ptr<HitRecord>(meshTriangle.intersect(&r));
    }
  }
}
BENCHMARK(BM_MeshTriangleTntersect);

}  // namespace
