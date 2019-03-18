#include "math/vector3f.h"
#include <gtest/gtest.h>
#include <iostream>
#include "math/vector4f.h"

TEST(Vector3f, create_with_arguments) {
  auto d = Vector3f(1, 2, 3);
  ASSERT_EQ(1, d.x);
  ASSERT_EQ(2, d.y);
  ASSERT_EQ(3, d.z);
}

TEST(Vector3f, create_from_other) {
  auto other = Vector3f(1, 2, 3);
  auto p = Vector3f(other);
  ASSERT_EQ(1, p.x);
  ASSERT_EQ(2, p.y);
  ASSERT_EQ(3, p.z);
}

TEST(Vector3f, create_from_vector4) {
  auto other = Vector4f(1, 2, 3, 4);
  auto p = Vector3f(other);
  ASSERT_EQ(1, p.x);
  ASSERT_EQ(2, p.y);
  ASSERT_EQ(3, p.z);
}

TEST(Vector3f, new_without_arguments) {
  auto d = Vector3f();
  ASSERT_EQ(0, d.x);
  ASSERT_EQ(0, d.y);
  ASSERT_EQ(0, d.z);
}

TEST(Vector3f, dot) {
  auto d = Vector3f(0, 3, 4);
  ASSERT_EQ(25, d.dot());
}

TEST(Vector3f, dot_with_other) {
  auto d = Vector3f(1, 2, 3);
  auto p = Vector3f(10, 20, 30);
  ASSERT_EQ(140, d.dot(p));
}

TEST(Vector3f, scale) {
  auto p = Vector3f(10, 20, 30);
  p.scale(0.1);
  ASSERT_EQ(1, p.x);
  ASSERT_EQ(2, p.y);
  ASSERT_EQ(3, p.z);
}

TEST(Vector3f, normalize) {
  auto p = Vector3f(10, 20, 30);
  p.normalize();
  ASSERT_EQ(1, p.dot());

  auto q = Vector3f(1, -1, 1);
  // 0.57735  -0.57735   0.57735
  q.normalize();

  float eps = 1e-6;
  ASSERT_NEAR(0.57735, q.x, eps);
  ASSERT_NEAR(-0.57735, q.y, eps);
  ASSERT_NEAR(0.57735, q.z, eps);
}

TEST(Vector3f, normalize_zero) {
  Vector3f p;
  p.normalize();
  ASSERT_EQ(0, p.dot());
}

TEST(Vector3f, sub) {
  auto p = Vector3f(9, 1, 7.5);
  auto q = Vector3f(1, 2, 3);
  p.sub(q);

  ASSERT_EQ(8, p.x);
  ASSERT_EQ(-1, p.y);
  ASSERT_EQ(4.5, p.z);
}

TEST(Vector3f, add) {
  auto p = Vector3f(9, -1, 7.5);
  auto q = Vector3f(1, -2, 3);
  p.add(q);

  ASSERT_EQ(10, p.x);
  ASSERT_EQ(-3, p.y);
  ASSERT_EQ(10.5, p.z);
}

TEST(Vector3f, negate) {
  auto p = Vector3f(1, -2, 3);
  p.negate();

  ASSERT_EQ(-1, p.x);
  ASSERT_EQ(2, p.y);
  ASSERT_EQ(-3, p.z);
}

TEST(Vector3f, abs) {
  auto p = Vector3f(-1, -2, 3);
  p.abs();

  ASSERT_EQ(1, p.x);
  ASSERT_EQ(2, p.y);
  ASSERT_EQ(3, p.z);
}

TEST(Vector3f, cross) {
  auto p = Vector3f(2, 3, 4);
  auto q = Vector3f(5, 6, 7);
  auto u = p.cross(q);

  ASSERT_EQ(-3, u->x);
  ASSERT_EQ(6, u->y);
  ASSERT_EQ(-3, u->z);

  delete u;
}

TEST(Vector3f, norm) {
  auto p = Vector3f(1, -1, 1);
  float eps = 1e-4;
  ASSERT_NEAR(1.7321, p.norm(), eps);
}

TEST(Vector3f, reflected) {
  auto v = Vector3f(1, 2, 4);
  auto normal = Vector3f(0, 0, 1);
  auto r = v.invReflected(normal);

  // reflected := v - 2 * dot(v, normal) * normal
  // dot(v, normal) = 4
  // 2 * dot(v, normal) * normal = (0, 0, 8)
  // r = (1, 2, 4) - (0, 0, 8) = (1, 2, -4)
  // invReflected = -reflected

  ASSERT_EQ(-1, r->x);
  ASSERT_EQ(-2, r->y);
  ASSERT_EQ(4, r->z);

  delete r;
}

TEST(Vector3f, scaleAdd) {
  auto v = Vector3f();
  auto base = Vector3f(2, 3, 4);
  auto other = Vector3f(1, 2, -3);
  float scale = 2.5;

  v.scaleAdd(scale, base, other);

  ASSERT_EQ(6, v.x);
  ASSERT_EQ(9.5, v.y);
  ASSERT_EQ(7, v.z);
}

TEST(Vector3f, scaleAddWithoutBase) {
  auto v = Vector3f(2, 3, 4);
  auto other = Vector3f(1, 2, -3);
  float scale = 2.5;

  v.scaleAdd(scale, other);

  ASSERT_EQ(6, v.x);
  ASSERT_EQ(9.5, v.y);
  ASSERT_EQ(7, v.z);
}
