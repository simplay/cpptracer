#include "intersectables/boundingBox.h"
#include <gtest/gtest.h>
#include <vector>
#include "math/vector3f.h"

TEST(BoundingBox, buildFromVectors) {
  auto vectors = std::vector<Vector3f>();

  auto v1 = Vector3f(-1, 2, 0);
  auto v2 = Vector3f(0, -2, 3);
  auto v3 = Vector3f(1, 0, -3);
  auto v4 = Vector3f(1.5, 1.5, -3.5);

  vectors.push_back(v1);
  vectors.push_back(v2);
  vectors.push_back(v3);
  vectors.push_back(v4);

  auto aabb = BoundingBox::buildFromVectors(vectors);

  ASSERT_EQ(-1, aabb.getBottomLeft().x);
  ASSERT_EQ(-2, aabb.getBottomLeft().y);
  ASSERT_EQ(-3.5, aabb.getBottomLeft().z);

  ASSERT_EQ(1.5, aabb.getTopRight().x);
  ASSERT_EQ(2, aabb.getTopRight().y);
  ASSERT_EQ(3, aabb.getTopRight().z);
}

TEST(BoundingBox, transform) {
  auto aabb = BoundingBox(Vector3f(0, 0, 0), Vector3f(1, 1, 1));

  // clang-format off
  auto transform = Matrix4f(
    1.0, 0.0, 0.0, 2.2,
    0.0, 1.0, 0.0, -10.2,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
  );
  // clang-format on

  auto transformedBoundingBox = aabb.transform(transform);

  auto bottomLeft = transformedBoundingBox.getBottomLeft();
  auto topRight = transformedBoundingBox.getTopRight();

  ASSERT_NEAR(2.2, bottomLeft.x, 1e-5);
  ASSERT_NEAR(-10.2, bottomLeft.y, 1e-5);
  ASSERT_NEAR(0, bottomLeft.z, 1e-5);

  ASSERT_NEAR(3.2, topRight.x, 1e-5);
  ASSERT_NEAR(-9.2, topRight.y, 1e-5);
  ASSERT_NEAR(1, topRight.z, 1e-5);
}

TEST(BoundingBox, overlaps) {
  auto bb1 = BoundingBox(Vector3f(0), Vector3f(1));
  auto bb2 = BoundingBox(Vector3f(0), Vector3f(0.5));
  auto bb3 = BoundingBox(Vector3f(-1), Vector3f(-0.5));

  EXPECT_TRUE(bb1.overlaps(bb2));
  EXPECT_FALSE(bb1.overlaps(bb3));
}

TEST(BoundingBox, overlaps_window) {
  auto bb1 = BoundingBox(Vector3f(0, 0, 0), Vector3f(1, 0, 0));
  auto bb2 = BoundingBox(Vector3f(0.75, 0, 0), Vector3f(1.25, 0, 0));
  EXPECT_TRUE(bb1.overlaps(bb2));
}

TEST(BoundingBox, overlaps_edge) {
  auto bb1 = BoundingBox(Vector3f(0, 0, 0), Vector3f(1, 0, 0));
  auto bb2 = BoundingBox(Vector3f(1, 0, 0), Vector3f(1.25, 0, 0));
  EXPECT_TRUE(bb1.overlaps(bb2));
}

TEST(BoundingBox, overlaps_corner) {
  auto bb1 = BoundingBox(Vector3f(0), Vector3f(1));
  auto bb2 = BoundingBox(Vector3f(-1), Vector3f(0));
  EXPECT_TRUE(bb1.overlaps(bb2));
}

TEST(BoundingBox, overlaps_corner_section) {
  auto bb1 = BoundingBox(Vector3f(0, 0, 0), Vector3f(1));
  auto bb2 = BoundingBox(Vector3f(0.75), Vector3f(1.25));
  EXPECT_TRUE(bb1.overlaps(bb2));
}

TEST(BoundingBox, overlaps_on_top) {
  auto bb1 = BoundingBox(Vector3f(0), Vector3f(1));
  auto bb2 = BoundingBox(Vector3f(0), Vector3f(1));
  EXPECT_TRUE(bb1.overlaps(bb2));
}

TEST(BoundingBox, overlaps_inclusion) {
  auto bb1 = BoundingBox(Vector3f(0), Vector3f(1));
  auto bb2 = BoundingBox(Vector3f(0.25), Vector3f(0.5));
  EXPECT_TRUE(bb1.overlaps(bb2));
}

TEST(BoundingBox, no_overlap1) {
  auto bb1 = BoundingBox(Vector3f(0, 0, 0), Vector3f(1, 1, 1));
  auto bb2 = BoundingBox(Vector3f(2, 0, 0), Vector3f(3, 1, 1));
  EXPECT_FALSE(bb1.overlaps(bb2));
}

TEST(BoundingBox, no_overlap2) {
  auto bb1 = BoundingBox(Vector3f(0, 0, 0), Vector3f(1, 1, 1));
  auto bb2 = BoundingBox(Vector3f(2, 1, 3), Vector3f(3, 2, 4));
  EXPECT_FALSE(bb1.overlaps(bb2));
}
