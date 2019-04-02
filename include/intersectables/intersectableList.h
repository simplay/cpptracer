#ifndef INTERSECTABLE_LIST_H
#define INTERSECTABLE_LIST_H

#include <vector>
#include "intersectable.h"

class IntersectableList : public Intersectable {
 private:
  std::vector<Intersectable*>* container;

 public:
  IntersectableList();
  HitRecord* intersect(const Ray&) const;

  void put(Intersectable*);
};
#endif
