#include <limits>
#include "../hitRecord.h"
#include "../intersectables/intersectableList.h"

IntersectableList::IntersectableList() {
  container = new std::vector<Intersectable*>;
}

HitRecord* IntersectableList::intersect(Ray* ray) {
  float eps = 0.00001;
  float minT = std::numeric_limits<float>::max();

  HitRecord* hitRecord = new HitRecord();
  for(auto const& intersectable: *container) {
    auto currentHitRecord = intersectable->intersect(ray);
    if (!currentHitRecord->isValid()) {
      continue;
    }

    // find closest hitRecord
    float currentT = currentHitRecord->t;
    if (currentT < minT && currentT > eps) {
      minT = currentT;
      hitRecord = currentHitRecord;
    }
  }
  return hitRecord;
}
void IntersectableList::put(Intersectable* intersectable) {
  container->push_back(intersectable);
}
