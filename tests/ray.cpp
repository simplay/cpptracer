#include "ray.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(Ray, new_ray_with_args) {
  Vector3f* origin = new Vector3f(1, 2, 3);
  Vector3f* direction = new Vector3f(1, 2, 3);
  Ray* r = new Ray(origin, direction, false);

  ASSERT_EQ(origin->x, r->origin->x);
  ASSERT_EQ(origin->y, r->origin->y);
  ASSERT_EQ(origin->z, r->origin->z);

  ASSERT_EQ(direction->x, r->direction->x);
  ASSERT_EQ(direction->y, r->direction->y);
  ASSERT_EQ(direction->z, r->direction->z);
}

TEST(Ray, pointAt) {
  Vector3f* origin = new Vector3f(0, 0, 0);
  Vector3f* direction = new Vector3f(1, 0, 0);
  Ray* r = new Ray(origin, direction, false);

  Vector3f* p = r->pointAt(2);

  ASSERT_EQ(2, p->x);
  ASSERT_EQ(0, p->y);
  ASSERT_EQ(0, p->z);
}
