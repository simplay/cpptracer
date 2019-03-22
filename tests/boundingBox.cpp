#include "intersectables/boundingBox.h"
#include <gtest/gtest.h>
#include "math/vector3f.h"
#include <vector>

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
