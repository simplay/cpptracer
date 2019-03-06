#include <math.h>
#include "intersectable.h"
#include "../math/vector3f.h"
#include "../hitRecord.h"
#include "../ray.h"

class Material;

#ifndef EXPLOSION_H
#define EXPLOSION_H
class Explosion : public Intersectable {
  public:
    Material* material;
    const Vector3f center;
    const float radius;

    Explosion(Material*, const Vector3f, float);

    virtual HitRecord* intersect(Ray* ray) const;
    float signed_distance(const Vector3f& p) const;
    float fractal_brownian_motion(const Vector3f& x) const;
    Vector3f rotate(const Vector3f& v) const;
    float noise(const Vector3f& x) const;

    template <typename T> inline T lerp(const T &v0, const T &v1, float t) const {
      return v0 + (v1-v0)*std::max(0.f, std::min(1.f, t));
    }

    float hash(const float n) const {
      float x = sin(n) * 43758.5453f;
      return x - floor(x);
    }
};
#endif
