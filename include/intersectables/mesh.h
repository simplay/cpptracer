#ifndef MESH_H
#define MESH_H

#include <string>
#include <limits>
#include "intersectableList.h"
#include "boundingBox.h"

class Mesh : public IntersectableList {
 private:
  Material* material;
 public:
  Mesh(Material*, std::string);

  BoundingBox getBoundingBox() const {
    float minT = std::numeric_limits<float>::min();
    float maxT = std::numeric_limits<float>::max();

    auto minX = maxT;
    auto minY = maxT;
    auto minZ = maxT;

    auto maxX = minT;
    auto maxY = minT;
    auto maxZ = minT;

    for (auto const& intersectable : *container) {
      auto boundingBox = intersectable->getBoundingBox();
      auto bottomLeft = boundingBox.getBottomLeft();
      auto topRight = boundingBox.getTopRight();


      minX = std::min((double)bottomLeft.x, (double)minX);
      minY = std::min((double)bottomLeft.y, (double)minY);
      minZ = std::min((double)bottomLeft.z, (double)minZ);

      maxX = std::max((double)topRight.x, (double)maxX);
      maxY = std::max((double)topRight.y, (double)maxY);
      maxZ = std::max((double)topRight.z, (double)maxZ);
    }

    return BoundingBox(Vector3f(minX, minY, minZ), Vector3f(maxX, maxY, maxZ));
  }
};
#endif
