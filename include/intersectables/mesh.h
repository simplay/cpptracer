#ifndef MESH_H
#define MESH_H

#include <limits>
#include <string>
#include "intersectables/accelerator/boundingBox.h"
#include "intersectableList.h"

class Mesh : public IntersectableList {
 private:
  Material* material;

 public:
  Mesh(Material*, std::string);
};
#endif
