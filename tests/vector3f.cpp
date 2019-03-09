#include <gtest/gtest.h>
#include <iostream>
#include "math/vector3f.h"
#include "math/vector4f.h"

TEST(Vector3f, create_with_arguments) {
  Vector3f d = Vector3f(1, 2, 3);
  ASSERT_EQ(1, d.x);
  ASSERT_EQ(2, d.y);
  ASSERT_EQ(3, d.z);
}

TEST(Vector3f, create_from_other) {
  Vector3f other = Vector3f(1, 2, 3);
  Vector3f p = Vector3f(other);
  ASSERT_EQ(1, p.x);
  ASSERT_EQ(2, p.y);
  ASSERT_EQ(3, p.z);
}

TEST(Vector3f, create_from_vector4) {
  Vector4f other = Vector4f(1, 2, 3, 4);
  Vector3f p = Vector3f(&other);
  ASSERT_EQ(1, p.x);
  ASSERT_EQ(2, p.y);
  ASSERT_EQ(3, p.z);
}

TEST(Vector3f, new_without_arguments) {
  Vector3f d = Vector3f();
  ASSERT_EQ(0, d.x);
  ASSERT_EQ(0, d.y);
  ASSERT_EQ(0, d.z);
}

TEST(Vector3f, dot) {
  Vector3f d = Vector3f(0, 3, 4);
  ASSERT_EQ(25, d.dot());
}

TEST(Vector3f, dot_with_other) {
  Vector3f d = Vector3f(1, 2, 3);
  Vector3f p = Vector3f(10, 20, 30);
  ASSERT_EQ(140, d.dot(&p));
}

TEST(Vector3f, scale) {
  Vector3f p = Vector3f(10, 20, 30);
  p.scale(0.1);
  ASSERT_EQ(1, p.x);
  ASSERT_EQ(2, p.y);
  ASSERT_EQ(3, p.z);
}

TEST(Vector3f, normalize) {
  Vector3f p = Vector3f(10, 20, 30);
  p.normalize();
  ASSERT_EQ(1, p.dot());
}

TEST(Vector3f, normalize_zero) {
  Vector3f p;
  p.normalize();
  ASSERT_EQ(0, p.dot());
}

TEST(Vector3f, sub) {
  Vector3f* p = new Vector3f(9, 1, 7.5);
  Vector3f* q = new Vector3f(1, 2, 3);
  p->sub(q);

  ASSERT_EQ(8, p->x);
  ASSERT_EQ(-1, p->y);
  ASSERT_EQ(4.5, p->z);
}

TEST(Vector3f, add) {
  Vector3f* p = new Vector3f(9, -1, 7.5);
  Vector3f* q = new Vector3f(1, -2, 3);
  p->add(q);

  ASSERT_EQ(10, p->x);
  ASSERT_EQ(-3, p->y);
  ASSERT_EQ(10.5, p->z);
}

TEST(Vector3f, negate) {
  Vector3f* p = new Vector3f(1, -2, 3);
  p->negate();

  ASSERT_EQ(-1, p->x);
  ASSERT_EQ(2, p->y);
  ASSERT_EQ(-3, p->z);
}

TEST(Vector3f, cross) {
  Vector3f* p = new Vector3f(2, 3, 4);
  Vector3f* q = new Vector3f(5, 6, 7);
  Vector3f* u = p->cross(q);

  ASSERT_EQ(-3, u->x);
  ASSERT_EQ(6, u->y);
  ASSERT_EQ(-3, u->z);
}

TEST(Vector3f, reflected) {
  Vector3f* v = new Vector3f(1, 2, 4);
  Vector3f* normal = new Vector3f(0, 0, 1);
  Vector3f* r = v->invReflected(normal);

  // reflected := v - 2 * dot(v, normal) * normal
  // dot(v, normal) = 4
  // 2 * dot(v, normal) * normal = (0, 0, 8)
  // r = (1, 2, 4) - (0, 0, 8) = (1, 2, -4)
  // invReflected = -reflected

  ASSERT_EQ(-1, r->x);
  ASSERT_EQ(-2, r->y);
  ASSERT_EQ(4, r->z);
}
