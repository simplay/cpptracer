#ifndef CSG_SOLID_H
#define CSG_SOLID_H

#include <limits>
#include "hitRecord.h"
#include "intersectables/accelerator/boundingBox.h"
#include "intersectables/intersectable.h"
#include "ray.h"

/**
 * A CsgSolid is an Intersectable that not just allows to get the closest hit
 * point - when intersected by a ray - but also allows to query the start-and
 * endpoint of an intersection with a ray (i.e. the so called intersection
 * interval).
 */
class CsgSolid : public Intersectable {
  BoundingBox aabb = BoundingBox(Vector3f(std::numeric_limits<float>::min()),
                                 Vector3f(std::numeric_limits<float>::max()));

  virtual HitRecord* intersect(const Ray& ray) const;
  virtual const BoundingBox& getBoundingBox() const;
};
#endif
