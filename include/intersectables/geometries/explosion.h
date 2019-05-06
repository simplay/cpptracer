#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <math.h>
#include "hitRecord.h"
#include "intersectables/accelerator/boundingBox.h"
#include "intersectables/intersectable.h"
#include "math/vector3f.h"
#include "ray.h"

class Material;

class Explosion : public Intersectable {
 private:
  Material* material;
  const Vector3f center;
  const float radius;

  float signed_distance(const Vector3f& p) const;
  float fractal_brownian_motion(const Vector3f& x) const;
  Vector3f rotate(const Vector3f& v) const;
  float noise(const Vector3f& x) const;

  template <typename T>
  inline T lerp(const T& v0, const T& v1, float t) const {
    return v0 + (v1 - v0) * std::max(0.f, std::min(1.f, t));
  }

  float hash(const float n) const {
    float x = sin(n) * 43758.5453f;
    return x - floor(x);
  }

  BoundingBox initBoundingBox() { return BoundingBox(Vector3f(0, 0, 0), Vector3f(0, 0, 0)); }

  BoundingBox aabb;

 public:
  Explosion(Material*, const Vector3f&, float);
  virtual HitRecord* intersect(const Ray& ray) const;
  const BoundingBox& getBoundingBox() const;
};
#endif
