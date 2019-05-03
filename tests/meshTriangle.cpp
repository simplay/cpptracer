#include "intersectables/meshTriangle.h"
#include <gtest/gtest.h>
#include <iostream>
#include "materials/diffuse.h"
#include "math/vector3f.h"
#include "spectrum.h"

TEST(MeshTriangle, getBoundingBox) {
  auto a = Vector3f(-1, 0, 3);
  auto b = Vector3f(1, -2, 0);
  auto c = Vector3f(0, 2, -3);
  auto d = Vector3f(0, 0, 0);
  auto s = Spectrum(0.0, 0.5, 0.5);
  auto diffuse = Diffuse(&s);
  auto tri = MeshTriangle(1, &diffuse, a, b, c, d, d, d);

  auto bb = tri.getBoundingBox();

  auto bottomLeft = bb.getBottomLeft();
  auto topRight = bb.getTopRight();

  ASSERT_EQ(-1, bottomLeft.x);
  ASSERT_EQ(-2, bottomLeft.y);
  ASSERT_EQ(-3, bottomLeft.z);

  ASSERT_EQ(1, topRight.x);
  ASSERT_EQ(2, topRight.y);
  ASSERT_EQ(3, topRight.z);
}
