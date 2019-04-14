#include "boundingBox.h"
#include <algorithm>
#include <limits>
#include "logger.h"

BoundingBox::BoundingBox(const Vector3f& bottomLeft, const Vector3f& topRight)
    : bottomLeft(bottomLeft), topRight(topRight) {}
HitRecord* BoundingBox::intersect(const Ray& ray) const { return new HitRecord(); }

BoundingBox BoundingBox::buildFromVectors(const std::vector<Vector3f>& vectors) {
  float minT = std::numeric_limits<float>::min();
  float maxT = std::numeric_limits<float>::max();

  auto minX = maxT;
  auto minY = maxT;
  auto minZ = maxT;

  auto maxX = minT;
  auto maxY = minT;
  auto maxZ = minT;

  // The bounding box is spanned by the find the minimum and maximum
  // components.
  for (auto v : vectors) {
    minX = std::min((double)v.x, (double)minX);
    minY = std::min((double)v.y, (double)minY);
    minZ = std::min((double)v.z, (double)minZ);

    maxX = std::max((double)v.x, (double)maxX);
    maxY = std::max((double)v.y, (double)maxY);
    maxZ = std::max((double)v.z, (double)maxZ);
  }

  auto bottomLeft = Vector3f(minX, minY, minZ);
  auto topRight = Vector3f(maxX, maxY, maxZ);

  return BoundingBox(bottomLeft, topRight);
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
