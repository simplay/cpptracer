#include <gtest/gtest.h>
#include "point3f.h"
#include <iostream>

TEST(Point3f, create_with_arguments) {
  Point3f d = Point3f(1, 2, 3);
  ASSERT_EQ(1, d.x);
  ASSERT_EQ(2, d.y);
  ASSERT_EQ(3, d.z);
}

TEST(Point3f, create_from_other) {
  Point3f other = Point3f(1, 2, 3);
  Point3f p = Point3f(other);
  ASSERT_EQ(1, p.x);
  ASSERT_EQ(2, p.y);
  ASSERT_EQ(3, p.z);
}

TEST(Point3f, new_without_arguments) {
  Point3f d = Point3f();
  ASSERT_EQ(0, d.x);
  ASSERT_EQ(0, d.y);
  ASSERT_EQ(0, d.z);
}

TEST(Point3f, dot) {
  Point3f d = Point3f(0, 3, 4);
  ASSERT_EQ(25, d.dot());
}

TEST(Point3f, scale) {
  Point3f p = Point3f(10, 20, 30);
  p.scale(0.1);
  ASSERT_EQ(1, p.x);
  ASSERT_EQ(2, p.y);
  ASSERT_EQ(3, p.z);
}

TEST(Point3f, normalize) {
  Point3f p = Point3f(10, 20, 30);
  p.normalize();
  ASSERT_EQ(1, p.dot());
}

TEST(Point3f, normalize_zero) {
  Point3f p;
  p.normalize();
  ASSERT_EQ(0, p.dot());
}

TEST(Point3f, sub) {
  Point3f* p = new Point3f(9, 1, 7.5);
  Point3f* q = new Point3f(1, 2, 3);
  p->sub(q);

  ASSERT_EQ(8, p->x);
  ASSERT_EQ(-1, p->y);
  ASSERT_EQ(4.5, p->z);
}

TEST(Point3f, add) {
  Point3f* p = new Point3f(9, -1, 7.5);
  Point3f* q = new Point3f(1, -2, 3);
  p->add(q);

  ASSERT_EQ(10, p->x);
  ASSERT_EQ(-3, p->y);
  ASSERT_EQ(10.5, p->z);
}

TEST(Point3f, cross) {
  Point3f* p = new Point3f(2, 3, 4);
  Point3f* q = new Point3f(5, 6, 7);
  Point3f* u = p->cross(q);

  ASSERT_EQ(-3, u->x);
  ASSERT_EQ(6, u->y);
  ASSERT_EQ(-3, u->z);
}
