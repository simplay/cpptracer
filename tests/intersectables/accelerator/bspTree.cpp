#include "intersectables/accelerator/bspTree.h"
#include <gtest/gtest.h>
#include <iostream>
#include "hitRecord.h"
#include "intersectables/containers/mesh.h"
#include "materials/diffuse.h"
#include "math/vector3f.h"
#include "ray.h"
#include "spectrum.h"

TEST(BspTree, buildTree) {
  auto s = Spectrum(0.0, 0.5, 0.5);
  auto diffuse = Diffuse(&s);
  auto mesh = Mesh(&diffuse, "../meshes/demo.obj");
  BspTree kdTree = BspTree(&mesh, 2, 4);
}

TEST(BspTree, intersect) {
  auto s = Spectrum(0.0, 0.5, 0.5);
  auto diffuse = Diffuse(&s);
  auto mesh = Mesh(&diffuse, "../meshes/demo.obj");
  auto kdTree = BspTree(&mesh, 2, 4);
  auto origin = new Vector3f(0);
  auto dir = new Vector3f(1, 0, 0);
  auto ray = Ray(origin, dir);
  IntersectableList* intersectableList = new IntersectableList();
  intersectableList->put(&kdTree);
  auto hit = intersectableList->intersect(ray);

  // ASSERT_TRUE(hit->isValid());
}
