#include "sphere.h"
#include <gtest/gtest.h>
#include "materials/diffuse.h"
#include "math/vector3f.h"
#include "spectrum.h"

TEST(Sphere, getBoundingBox) {
  auto s = Spectrum(0.0, 0.5, 0.5);
  auto diffuse = Diffuse(&s);

  auto center = Vector3f(1.0, 2.5, -1.0);
  auto sphere = Sphere(&diffuse, center, 0.5f);

  auto bb = sphere.getBoundingBox();

  auto bottomLeft = bb.getBottomLeft();
  auto topRight = bb.getTopRight();

  ASSERT_EQ(0.5, bottomLeft.x);
  ASSERT_EQ(2.0, bottomLeft.y);
  ASSERT_EQ(-1.5, bottomLeft.z);

  ASSERT_EQ(1.5, topRight.x);
  ASSERT_EQ(3.0, topRight.y);
  ASSERT_EQ(-0.5, topRight.z);
}
