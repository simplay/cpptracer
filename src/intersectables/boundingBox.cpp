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
