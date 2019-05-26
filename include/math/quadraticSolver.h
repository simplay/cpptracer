#ifndef QUADRATIC_SOLVER_H
#define QUADRATIC_SOLVER_H

#include <string>
#include <vector>

/**
 * Float valued point with 3 coordinates.
 */
class QuadraticSolver {
 private:
  float a;
  float b;
  float c;

 public:
  QuadraticSolver(const float a, const float b, const float c);
  std::vector<float> solve();
};
#endif
