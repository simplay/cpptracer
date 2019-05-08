#ifndef CUBE_H
#define CUBE_H

#include <limits>
#include "hitRecord.h"
#include "intersectables/accelerator/boundingBox.h"
#include "intersectables/containers/intersectableList.h"
#include "intersectables/csg/csgNode.h"
#include "intersectables/csg/csgSolid.h"
#include "intersectables/geometries/plane.h"
#include "math/vector3f.h"
#include "ray.h"

class Material;

class Cube : public CsgSolid {
 private:
  IntersectableList* sides;
  Material* material;
  const BoundingBox aabb;
  CsgNode* root;

  BoundingBox computeAABB() {
    return BoundingBox(Vector3f(std::numeric_limits<float>::min()),
                       Vector3f(std::numeric_limits<float>::max()));
  }

  CsgNode* computeRootNode(const Material*) {
    auto right = new Plane(material, Vector3f(1.f, 0.f, 0.f), -1.0);
    auto left = new Plane(material, Vector3f(-1.f, 0.f, 0.f), -1.0);
    auto top = new Plane(material, Vector3f(0.f, 1.f, 0.f), -1.0);
    auto bottom = new Plane(material, Vector3f(0.f, -1.f, 0.f), -1.0);
    auto front = new Plane(material, Vector3f(0.f, 0.f, 1.f), -1.0);
    auto back = new Plane(material, Vector3f(0.f, 0.f, -1.f), -1.0);

    sides->put(right);
    sides->put(left);
    sides->put(top);
    sides->put(bottom);
    sides->put(front);
    sides->put(back);

    auto n1 = new CsgNode(top, left, SetOperation::INTERSECTION);
    auto n2 = new CsgNode(top, bottom, SetOperation::INTERSECTION);
    auto n3 = new CsgNode(front, back, SetOperation::INTERSECTION);
    auto n4 = new CsgNode(n1, n2, SetOperation::INTERSECTION);
    return new CsgNode(n3, n4, SetOperation::INTERSECTION);
  }

  HitRecord* buildHitRecord(float t, const Ray& ray) const;

 public:
  Cube(Material*);
  virtual HitRecord* intersect(const Ray& ray) const;

  const BoundingBox& getBoundingBox() const { return aabb; }
  virtual std::vector<IntervalBoundary> getIntervalBoundaries(const Ray& ray) const;
};
#endif
