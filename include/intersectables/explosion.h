#include <math.h>
#include "intersectable.h"
#include "../math/point3f.h"
#include "../hitRecord.h"
#include "../ray.h"

class Material;

#ifndef EXPLOSION_H
#define EXPLOSION_H
class Explosion : public Intersectable {
  public:
    Material* material;
    const Point3f center;
    const float radius;

    Explosion(Material*, const Point3f, float);

    virtual HitRecord* intersect(Ray* ray) const;
    float signed_distance(const Point3f& p) const;
    float fractal_brownian_motion(const Point3f& x) const;
    Point3f rotate(const Point3f& v) const;
    float noise(const Point3f& x) const;

    template <typename T> inline T lerp(const T &v0, const T &v1, float t) const {
      return v0 + (v1-v0)*std::max(0.f, std::min(1.f, t));
    }

    float hash(const float n) const {
      float x = sin(n) * 43758.5453f;
      return x - floor(x);
    }
};
#endif
