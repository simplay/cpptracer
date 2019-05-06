#include <gtest/gtest.h>
#include "intersectables/mesh.h"
#include "materials/diffuse.h"
#include "math/vector3f.h"
#include "spectrum.h"

TEST(Mesh, getBoundingBox) {
  auto s = Spectrum(0.0, 0.5, 0.5);
  auto diffuse = Diffuse(&s);
  auto mesh = Mesh(&diffuse, "../meshes/demo.obj");

  auto bb = mesh.getBoundingBox();

  auto bottomLeft = bb.getBottomLeft();
  auto topRight = bb.getTopRight();

  ASSERT_EQ(0, bottomLeft.x);
  ASSERT_EQ(0, bottomLeft.y);
  ASSERT_EQ(0, bottomLeft.z);

  ASSERT_EQ(1, topRight.x);
  ASSERT_EQ(1, topRight.y);
  ASSERT_NEAR(0, topRight.z, 1e-5);
}
