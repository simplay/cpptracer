#include "math/vector4f.h"
#include <benchmark/benchmark.h>

static void BM_Vector4fDot(benchmark::State& state) {
  auto p = Vector4f(1, -2, 3, 4);
  auto q = Vector4f(-10, 20, 30, 40);

  for (auto _ : state)
    // Result is not used, wrap with benchmark::DoNotOptimize to guarantee it remains.
    benchmark::DoNotOptimize(p.dot(q));
}
BENCHMARK(BM_Vector4fDot);

BENCHMARK_MAIN();
