#include "intersectableList.h"

#ifndef MESH_H
#define MESH_H
class Mesh : public IntersectableList {
  private:
    Material* material;

  public:
    Mesh(Material*);
};
#endif
