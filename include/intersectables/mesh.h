#include <string>
#include "intersectableList.h"

#ifndef MESH_H
#define MESH_H
class Mesh : public IntersectableList {
 private:
  Material* material;
  std::string filepath;

 public:
  Mesh(Material*, std::string);
};
#endif
