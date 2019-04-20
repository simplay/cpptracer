#ifndef INTERSECTABLE_LIST_H
#define INTERSECTABLE_LIST_H

#include <limits>
#include <vector>
#include "boundingBox.h"
#include "intersectable.h"

class IntersectableList : public Intersectable {
 private:
  std::vector<Intersectable*> initContainer() {
    auto _container = std::vector<Intersectable*>();
    _container.reserve(1000);
    return _container;
  }

  BoundingBox computeBoundingBox();

 protected:
  std::vector<Intersectable*> container;
  BoundingBox aabb;

 public:
  IntersectableList();

  HitRecord* intersect(const Ray&) const;
  const BoundingBox& getBoundingBox() const;

  void put(Intersectable*);
  int size() const;

  const std::vector<Intersectable*> getContainer() const {
    return container;
  }
};
#endif
