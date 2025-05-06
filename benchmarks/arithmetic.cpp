#include "./bench_common.hpp"

static void lazy_expr(benchmark::State &state) {
  using namespace nda;
  volatile int N = static_cast<int>(state.range(0)); // Prevent compile-time optimization

  matrix<double> A = 1 + rand<double>(N, N);
  matrix<double> B = 1 + rand<double>(N, N);
  matrix<double> C = 1 + rand<double>(N, N);
  matrix<double> D = 1 + rand<double>(N, N);
  matrix<double> E = 1 + zeros<double>(N, N);
  benchmark::DoNotOptimize(A.data());
  benchmark::DoNotOptimize(B.data());
  benchmark::DoNotOptimize(C.data());
  benchmark::DoNotOptimize(D.data());
  benchmark::DoNotOptimize(E.data());


  while (state.KeepRunning()) { benchmark::DoNotOptimize(E = ((2.0 * A + B * C - 0.5 * D) / (A + 0.1)) + (C - B / (D + 1.0))); }
}

// Register benchmark with different runtime sizes
BENCHMARK(lazy_expr)
   ->DenseRange(500, 1000, 250)
   ->Iterations(10) // 10 iterations per size
   ->Unit(benchmark::kMillisecond);
