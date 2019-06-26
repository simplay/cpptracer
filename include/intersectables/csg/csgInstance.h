#ifndef CSG_INSTANCE_H
#define CSG_INSTANCE_H

#include "hitRecord.h"
#include "intersectables/accelerator/boundingBox.h"
#include "intersectables/containers/instance.h"
#include "intersectables/csg/csgSolid.h"
#include "math/matrix4f.h"
#include "math/vector3f.h"
#include "ray.h"

class CsgInstance : public CsgSolid {
 private:
  CsgSolid* solid;

  // homogeneous tranformation matrix T described in local object coordinate
  // system, i.e. from object coordinates to world coords.
  Matrix4f* transformation;

  // homogeneous inverse tranformation T^-1 described in world coordinate
  // system, i.e. from world space coordinates to local coords.
  Matrix4f* invTransformation;

  // homogeneous transposed inverse tranformation (T^-1)^t used to transform
  // normals and tangent vectors, described in world coordinate system
  Matrix4f* invTrasnposedTransformation;

  BoundingBox aabb;

 public:
  CsgInstance(CsgSolid*);
  CsgInstance(CsgSolid*, Matrix4f*);
  std::vector<CsgSolid::IntervalBoundary> getIntervalBoundaries(const Ray& ray) const;

  virtual HitRecord* intersect(const Ray& ray) const;

  virtual const BoundingBox& getBoundingBox() const;
};
#endif
