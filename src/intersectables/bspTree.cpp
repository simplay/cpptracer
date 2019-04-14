#include "intersectables/bspTree.h"

BspTree::BspTree(const Intersectable& intersectable)
    : intersectable(intersectable), aabb(initBoundingBox()) {}

HitRecord* BspTree::intersect(const Ray& ray) const { return new HitRecord(); }

const BoundingBox& BspTree::getBoundingBox() const { return aabb; }
