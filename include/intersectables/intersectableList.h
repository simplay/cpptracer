#include <vector>
#include "intersectable.h"

#ifndef INTERSECTABLE_LIST_H
#define INTERSECTABLE_LIST_H
class IntersectableList : public Intersectable {
  private:
    std::vector<Intersectable*>* container;

  public:
    IntersectableList();
    virtual HitRecord* intersect(Ray*);
    void put(Intersectable*);
};
#endif
