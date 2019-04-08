#ifndef INTERSECTABLE_LIST_H
#define INTERSECTABLE_LIST_H

#include <vector>
#include "boundingBox.h"
#include "intersectable.h"

class IntersectableList : public Intersectable {
 protected:
  std::vector<Intersectable*>* container;

 public:
  IntersectableList();
  HitRecord* intersect(const Ray&) const;

  void put(Intersectable*);
  BoundingBox getBoundingBox() const {
    BoundingBox foo(Vector3f(0, 0, 0), Vector3f(0, 0, 0));
    return foo;
  }
};
#endif
