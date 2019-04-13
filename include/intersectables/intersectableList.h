#ifndef INTERSECTABLE_LIST_H
#define INTERSECTABLE_LIST_H

#include <limits>
#include <vector>
#include "boundingBox.h"
#include "intersectable.h"

class IntersectableList : public Intersectable {
 protected:
  std::vector<Intersectable*>* container;

 public:
  IntersectableList();
  HitRecord* intersect(const Ray&) const;
  BoundingBox getBoundingBox() const;

  void put(Intersectable*);
};
#endif
