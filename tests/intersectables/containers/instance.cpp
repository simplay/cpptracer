#include "intersectables/containers/instance.h"
#include <gtest/gtest.h>
#include "intersectables/accelerator/boundingBox.h"
#include "intersectables/geometries/triangle.h"
#include "materials/diffuse.h"
#include "math/vector3f.h"

TEST(Instance, getBoundingBox) {
  auto a = Vector3f(1, 0, 0);
  auto b = Vector3f(0, 1, 0);
  auto c = Vector3f(0, 0, 1);

  auto s = Spectrum(0.0, 0.5, 0.5);
  auto diffuse = Diffuse(&s);
  auto tri = Triangle(1, &diffuse, a, b, c);

  // clang-format off
  auto transform = Matrix4f(
    1.0, 0.0, 0.0, 2.2,
    0.0, 1.0, 0.0, -10.2,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
  );
  // clang-format on

  auto instance = new Instance(&tri, &transform);

  auto aabb = instance->getBoundingBox();
  // delete instance;

  auto bottomLeft = aabb.getBottomLeft();
  auto topRight = aabb.getTopRight();

  ASSERT_NEAR(2.2, bottomLeft.x, 1e-5);
  ASSERT_NEAR(-10.2, bottomLeft.y, 1e-5);
  ASSERT_NEAR(0, bottomLeft.z, 1e-5);

  ASSERT_NEAR(3.2, topRight.x, 1e-5);
  ASSERT_NEAR(-9.2, topRight.y, 1e-5);
  ASSERT_NEAR(1, topRight.z, 1e-5);
}

