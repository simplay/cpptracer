#ifndef MESH_H
#define MESH_H

#include <string>
#include <limits>
#include "intersectableList.h"
#include "boundingBox.h"

class Mesh : public IntersectableList {
 private:
  Material* material;
 public:
  Mesh(Material*, std::string);
};
#endif
