#include <vector>
#include "intersectable.h"

#ifndef INTERSECTABLE_LIST_H
#define INTERSECTABLE_LIST_H
class IntersectableList : public Intersectable {
  private:
    std::vector<Intersectable*>* container;
    const float EPSILON = 0.00001;

  public:
    IntersectableList();
    HitRecord* intersect(Ray*);
    void put(Intersectable*);
};
#endif
