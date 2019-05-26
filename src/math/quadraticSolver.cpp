#include "math/quadraticSolver.h"
#include <cmath>

QuadraticSolver::QuadraticSolver(const float a, const float b, const float c) : a(a), b(b), c(c) {}

std::vector<float> QuadraticSolver::solve() {
  std::vector<float> boundaries;

  float discriminant = b * b - 4.0 * a * c;

  if (discriminant < 0.0) {
    return boundaries;
  }

  float t1 = (-b + sqrt(discriminant)) / (2.0 * a);
  float t2 = (-b - sqrt(discriminant)) / (2.0 * a);

  boundaries.push_back(t1);
  boundaries.push_back(t2);

  return boundaries;
}
