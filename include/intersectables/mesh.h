#ifndef MESH_H
#define MESH_H

#include <string>
#include "intersectableList.h"
#include "boundingBox.h"

class Mesh : public IntersectableList {
 private:
  Material* material;
 public:
  Mesh(Material*, std::string);

  BoundingBox getBoundingBox() const {
    BoundingBox foo(Vector3f(0, 0, 0), Vector3f(0, 0, 0));
    return foo;
  }
};
#endif
