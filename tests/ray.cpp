#include <gtest/gtest.h>
#include <iostream>
#include "ray.h"

TEST(Ray, new_ray_no_args) {
  Ray* r = new Ray();

  ASSERT_EQ(0, r->origin->x);
  ASSERT_EQ(0, r->origin->y);
  ASSERT_EQ(0, r->origin->z);

  ASSERT_EQ(0, r->direction->x);
  ASSERT_EQ(0, r->direction->y);
  ASSERT_EQ(0, r->direction->z);
}

TEST(Ray, new_ray_with_args) {
  Point3f* origin = new Point3f(1, 2, 3);
  Point3f* direction = new Point3f(1, 2, 3);
  Ray* r = new Ray(origin, direction, 1.0);

  ASSERT_EQ(origin->x, r->origin->x);
  ASSERT_EQ(origin->y, r->origin->y);
  ASSERT_EQ(origin->z, r->origin->z);

  ASSERT_EQ(direction->x, r->direction->x);
  ASSERT_EQ(direction->y, r->direction->y);
  ASSERT_EQ(direction->z, r->direction->z);
}

TEST(Ray, pointAt) {
  Point3f* origin = new Point3f(0, 0, 0);
  Point3f* direction = new Point3f(1, 0, 0);
  Ray* r = new Ray(origin, direction, 1.0);

  Point3f* p = r->pointAt(2);

  ASSERT_EQ(2, p->x);
  ASSERT_EQ(0, p->y);
  ASSERT_EQ(0, p->z);
}
