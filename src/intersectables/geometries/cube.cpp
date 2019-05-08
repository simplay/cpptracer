#include "intersectables/geometries/cube.h"
#include <iostream>

Cube::Cube(Material* material)
    : sides(new IntersectableList()),
      material(material),
      aabb(computeAABB()),
      root(computeRootNode(material)) {}

std::vector<CsgSolid::IntervalBoundary> Cube::getIntervalBoundaries(const Ray& ray) const {
  return root->getIntervalBoundaries(ray);
}

HitRecord* Cube::intersect(const Ray& ray) const {
  return sides->intersect(ray);
}
