#include <gtest/gtest.h>
#include "spectrum.h"
#include "math/vector3f.h"

namespace {
  const float EPS = 1e-4;

TEST(Spectrum, new_without_arguments) {
  Spectrum s = Spectrum();
  ASSERT_NEAR(0, s.r, EPS);
  ASSERT_NEAR(0, s.g, EPS);
  ASSERT_NEAR(0, s.b, EPS);
}

TEST(Spectrum, new_with_floats) {
  auto s = Spectrum(0.5, 0.6, 0.7);
  ASSERT_NEAR(0.5, s.r, EPS);
  ASSERT_NEAR(0.6, s.g, EPS);
  ASSERT_NEAR(0.7, s.b, EPS);
}

TEST(Spectrum, new_with_float) {
  auto s = Spectrum(0.5);
  ASSERT_NEAR(0.5, s.r, EPS);
  ASSERT_NEAR(0.5, s.g, EPS);
  ASSERT_NEAR(0.5, s.b, EPS);
}

TEST(Spectrum, new_from_other) {
  auto other = Spectrum(0.5, 0.6, 0.7);
  auto s = Spectrum(other);
  ASSERT_NEAR(0.5, s.r, EPS);
  ASSERT_NEAR(0.6, s.g, EPS);
  ASSERT_NEAR(0.7, s.b, EPS);
}

TEST(Spectrum, new_from_vector3f) {
  auto v = new Vector3f(0.5, 0.6, 0.7);
  auto s = Spectrum(v);
  ASSERT_NEAR(0.5, s.r, EPS);
  ASSERT_NEAR(0.6, s.g, EPS);
  ASSERT_NEAR(0.7, s.b, EPS);
}

TEST(Spectrum, scale) {
  auto s = Spectrum(0.4, 0.5, 0.6);
  s.scale(1.5);
  ASSERT_NEAR(0.6, s.r, EPS);
  ASSERT_NEAR(0.75, s.g, EPS);
  ASSERT_NEAR(0.9, s.b, EPS);
}

TEST(Spectrum, add) {
  auto s = Spectrum(0.4, 0.5, 0.6);
  auto t = Spectrum(0.2, 0.25, 0.3);
  s.add(t);
  ASSERT_NEAR(0.6, s.r, EPS);
  ASSERT_NEAR(0.75, s.g, EPS);
  ASSERT_NEAR(0.9, s.b, EPS);
}

TEST(Spectrum, mult) {
  auto s = Spectrum(0.4, 0.5, 0.6);
  auto t = Spectrum(0.5, 0.1, 0.2);
  s.mult(t);
  ASSERT_NEAR(0.2, s.r, EPS);
  ASSERT_NEAR(0.05, s.g, EPS);
  ASSERT_NEAR(0.12, s.b, EPS);
}

TEST(Spectrum, clamp) {
  auto s = Spectrum(1.4, 2.5, 0.6);
  s.clamp();
  ASSERT_NEAR(1, s.r, EPS);
  ASSERT_NEAR(1, s.g, EPS);
  ASSERT_NEAR(0.6, s.b, EPS);
}

}
