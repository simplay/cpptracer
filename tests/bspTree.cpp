#include "bspTree.h"
#include <gtest/gtest.h>
#include <iostream>
#include "intersectables/mesh.h"
#include "materials/diffuse.h"
#include "math/vector3f.h"
#include "spectrum.h"

TEST(BspTree, buildTree) {
  auto s = Spectrum(0.0, 0.5, 0.5);
  auto diffuse = Diffuse(&s);
  auto mesh = Mesh(&diffuse, "../meshes/demo.obj");
  BspTree kdTree = BspTree(mesh, 2, 4);
}
