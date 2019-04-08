#include "intersectables/intersectableList.h"
#include <gtest/gtest.h>
#include "intersectables/triangle.h"
#include "materials/diffuse.h"
#include "math/vector3f.h"
#include "spectrum.h"

TEST(IntersectableList, getBoundingBox) {
  auto s = Spectrum(0.0, 0.5, 0.5);
  auto diffuse = Diffuse(&s);

  auto intersectableList = IntersectableList();
  auto tri = Triangle(1, &diffuse, Vector3f(0.0, 0.0, 0.0), Vector3f(1.0, 0.0, 0.0),
                      Vector3f(0.0, 1.0, 0.0));

  auto tri2 = Triangle(2, &diffuse, Vector3f(3.0, 3.0, 3.0), Vector3f(1.0, 0.0, 0.0),
                       Vector3f(0.0, 1.0, -1.0));

  intersectableList.put(&tri);
  intersectableList.put(&tri2);

  auto bb = intersectableList.getBoundingBox();

  auto bottomLeft = bb.getBottomLeft();
  auto topRight = bb.getTopRight();

  ASSERT_EQ(0, bottomLeft.x);
  ASSERT_EQ(0, bottomLeft.y);
  ASSERT_EQ(-1, bottomLeft.z);

  ASSERT_EQ(3, topRight.x);
  ASSERT_EQ(3, topRight.y);
  ASSERT_NEAR(3, topRight.z, 1e-5);
}
