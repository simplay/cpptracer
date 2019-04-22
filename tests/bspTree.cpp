#include "bspTree.h"
#include <gtest/gtest.h>
#include <iostream>
#include "intersectables/mesh.h"
#include "materials/diffuse.h"
#include "math/vector3f.h"
#include "spectrum.h"
#include "hitRecord.h"
#include "ray.h"

TEST(BspTree, buildTree) {
  auto s = Spectrum(0.0, 0.5, 0.5);
  auto diffuse = Diffuse(&s);
  auto mesh = Mesh(&diffuse, "../meshes/demo.obj");
  BspTree kdTree = BspTree(mesh, 2, 4);
}

TEST(BspTree, intersect) {
  auto s = Spectrum(0.0, 0.5, 0.5);
  auto diffuse = Diffuse(&s);
  auto mesh = Mesh(&diffuse, "../meshes/demo.obj");
  auto kdTree = BspTree(mesh, 2, 4);
  auto origin = new Vector3f(0);
  auto dir = new Vector3f(1, 0, 0);
  auto ray = Ray(origin, dir);
  auto hit = kdTree.intersect(ray);

  // ASSERT_TRUE(hit->isValid());
}
