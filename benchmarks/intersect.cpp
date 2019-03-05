#include <memory>
#include <benchmark/benchmark.h>
#include "point3f.h"
#include "../intersectables/explosion.h"
#include "../intersectables/plane.h"
#include "../intersectables/sphere.h"
#include "../intersectables/triangle.h"
#include "../materials/diffuse.h"

namespace {

std::vector<Ray> MakeRays() {
    return {
      Ray(new Point3f(1.0, 1.0, 1.0), new Point3f(-1, -1, -1)),
      Ray(new Point3f(-1.0, -1.0, -1.0), new Point3f(1, 1, 1)),
      Ray(new Point3f(0.5, 0.5, 1.0), new Point3f(0, 0, -1)),
      Ray(new Point3f(0.5, 0.5, -1.0), new Point3f(0, 0, 1)),
  };
}

static void BM_TriangleIntersect(benchmark::State& state) {
  Diffuse material = Diffuse(new Spectrum(1.0));
  auto triangle = Triangle(
    1,
    &material,
    new Point3f(0.0, 0.0, 0.0),
    new Point3f(1.0, 0.0, 0.0),
    new Point3f(0.0, 1.0, 0.0)
  );

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
  auto sphere = Sphere(
    &material,
    Point3f(0.0, 0.0, 0.0),
    1
  );

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
  auto explosion = Explosion(
    &material,
    Point3f(0.0, 0.0, 0.0),
    1
  );

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
  auto plane = Plane(
    &material,
    Point3f(0.0, 0.0, 0.0),
    1
  );

  auto rays = MakeRays();
  for (auto _ : state) {
    for (auto& r : rays) {
      std::unique_ptr<HitRecord>(plane.intersect(&r));
    }
  }
}
BENCHMARK(BM_PlaneIntersect);

}
