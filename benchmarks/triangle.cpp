#include <memory>
#include <benchmark/benchmark.h>
#include "point3f.h"
#include "../intersectables/triangle.h"
#include "../materials/diffuse.h"

static void BM_TriangleIntersect(benchmark::State& state) {
  Diffuse material = Diffuse(new Spectrum(1.0));
  auto triangle = Triangle(
    1,
    &material,
    new Point3f(0.0, 0.0, 0.0),
    new Point3f(1.0, 0.0, 0.0),
    new Point3f(0.0, 1.0, 0.0)
  );

  std::vector<Ray> rays({
      Ray(new Point3f(1.0, 1.0, 1.0), new Point3f(-1, -1, -1)),
      Ray(new Point3f(-1.0, -1.0, -1.0), new Point3f(1, 1, 1)),
      Ray(new Point3f(0.5, 0.5, 1.0), new Point3f(0, 0, -1)),
      Ray(new Point3f(0.5, 0.5, -1.0), new Point3f(0, 0, 1)),
  });

  for (auto _ : state) {
    // Result is not used, wrap with benchmark::DoNotOptimize to guarantee it remains.
    for (auto& r : rays) {
        std::unique_ptr<HitRecord>(triangle.intersect(&r));
    }
  }
}
BENCHMARK(BM_TriangleIntersect);