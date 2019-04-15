#include "boundingBox.h"
#include <algorithm>
#include <limits>

BoundingBox::BoundingBox(const Vector3f& bottomLeft, const Vector3f& topRight)
    : bottomLeft(bottomLeft), topRight(topRight) {}
HitRecord* BoundingBox::intersect(const Ray& ray) const { return new HitRecord(); }

BoundingBox BoundingBox::buildFromVectors(const std::vector<Vector3f>& vectors) {
  Vector3f min(std::numeric_limits<float>::max());
  Vector3f max(std::numeric_limits<float>::min());

  // The bounding box is spanned by the find the minimum and maximum
  // components.
  for (auto v : vectors) {
    min.x = std::min(v.x, min.x);
    min.y = std::min(v.y, min.y);
    min.z = std::min(v.z, min.z);

    max.x = std::max(v.x, max.x);
    max.y = std::max(v.y, max.y);
    max.z = std::max(v.z, max.z);
  }

  return BoundingBox(min, max);
}

const BoundingBox& BoundingBox::getBoundingBox() const { return *this; }

BoundingBox BoundingBox::transform(Matrix4f& transformation) const {
  auto transformedBottomLeft = transformation.mult(Vector4f(bottomLeft, 1))->toVector3f();
  auto transformedTopRight = transformation.mult(Vector4f(topRight, 1))->toVector3f();

  auto transformedBoundingBox = BoundingBox(*transformedBottomLeft, *transformedTopRight);

  delete transformedBottomLeft;
  delete transformedTopRight;

  return transformedBoundingBox;
}

void BoundingBox::expand(const Intersectable* intersectable) {
  auto otherBB = intersectable->getBoundingBox();

  auto minX = std::min((double)bottomLeft.x, (double)otherBB.getBottomLeft().x);
  auto minY = std::min((double)bottomLeft.y, (double)otherBB.getBottomLeft().y);
  auto minZ = std::min((double)bottomLeft.z, (double)otherBB.getBottomLeft().z);

  auto maxX = std::max((double)topRight.x, (double)otherBB.getTopRight().x);
  auto maxY = std::max((double)topRight.y, (double)otherBB.getTopRight().y);
  auto maxZ = std::max((double)topRight.z, (double)otherBB.getTopRight().z);

  *(Vector3f*)&bottomLeft = Vector3f(minX, minY, minZ);
  *(Vector3f*)&topRight = Vector3f(maxX, maxY, maxZ);
}
