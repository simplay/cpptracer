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
    Point3f* center;
    float radius;

    Explosion(Material*, Point3f*, float);

    virtual HitRecord* intersect(Ray* ray) const;
    float signed_distance(Point3f* p) const;
    float fractal_brownian_motion(Point3f* x) const;
    Point3f rotate(Point3f* v) const;
    float noise(Point3f* x) const;

    template <typename T> inline T lerp(const T &v0, const T &v1, float t) const {
      return v0 + (v1-v0)*std::max(0.f, std::min(1.f, t));
    }

    float hash(const float n) const {
      float x = sin(n) * 43758.5453f;
      return x - floor(x);
    }
};
#endif
