#ifndef INSTANCE_H
#define INSTANCE_H

#include "../hitRecord.h"
#include "../math/matrix4f.h"
#include "../math/vector3f.h"
#include "../ray.h"
#include "intersectable.h"

class Material;

/**
 * Used to reduce memory usage: Instead re-creating very similar intersectables,
 * try to re-use them.
 *
 * An instance has a reference shadered intersectable and a homogeneous
 * tranformation which describes how an object is rotated, translated, scaled
 * and sheared in its using scene.
 *
 * An instance of an intersectable then never gets modified, only its
 * transformation matrix gets updated. This allows to save us from creating
 * many similar intersectable instances
 */
class Instance : public Intersectable {
 private:
  // A reference to an intersectable, e.g. a sphere or a plane.
  Intersectable* intersectable;

  // homogeneous tranformation matrix T described in local object coordinate
  // system, i.e. from object coordinates to world coords.
  Matrix4f* transformation;

  // homogeneous inverse tranformation T^-1 described in world coordinate
  // system, i.e. from world space coordinates to local coords.
  Matrix4f* invTransformation;

  // homogeneous transposed inverse tranformation (T^-1)^t used to transform
  // normals and tangent vectors, described in world coordinate system
  Matrix4f* invTrasnposedTransformation;

 public:
  Instance(Intersectable*);
  Instance(Intersectable*, Matrix4f*);
  ~Instance();

  HitRecord* intersect(const Ray& ray) const;
};
#endif
