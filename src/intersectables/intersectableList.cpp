#include "intersectables/intersectableList.h"
#include <limits>
#include "hitRecord.h"

class BoundingBox;

IntersectableList::IntersectableList() { container = new std::vector<Intersectable*>; }

HitRecord* IntersectableList::intersect(const Ray& ray) const {
  float minT = std::numeric_limits<float>::max();
  auto hitRecord = new HitRecord();
  for (auto const& intersectable : *container) {
    HitRecord* currentHitRecord = intersectable->intersect(ray);
    if (!currentHitRecord->isValid()) {
      delete currentHitRecord;
      continue;
    }

    // find closest hitRecord
    float currentT = currentHitRecord->t;
    if (currentT < minT && currentT > 0.0) {
      minT = currentT;
      delete hitRecord;
      hitRecord = new HitRecord(currentHitRecord);
    }

    // only delete the current hitRecord if there is more than one intersectable in the scene
    if (container->size() > 1) {
      delete currentHitRecord;
    }
  }

  return hitRecord;
}

BoundingBox IntersectableList::getBoundingBox() const {
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

void IntersectableList::put(Intersectable* intersectable) { container->push_back(intersectable); }
