#include "intersectables/bspTree.h"

BspTree::BspTree(const Intersectable& intersectable) : intersectable(intersectable) {}

HitRecord* BspTree::intersect(const Ray& ray) const { return new HitRecord(); }

BoundingBox BspTree::getBoundingBox() const {
  BoundingBox foo(Vector3f(0, 0, 0), Vector3f(0, 0, 0));
  return foo;
}
