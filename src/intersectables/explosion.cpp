#include <iostream>
#include <cmath>
#include "explosion.h"

Explosion::Explosion(Material* material, const Point3f center, float radius)
  : material(material), center(center), radius(radius)
{}

HitRecord* Explosion::intersect(Ray* ray) const {
  const Point3f& orig = *ray->origin;
  const Point3f& dir = *ray->direction;
  if (orig.dot() - pow(orig.dot(&dir), 2) > pow(radius, 2)) {
    return new HitRecord();
  }

  Point3f hitPos = orig;
  for (size_t i = 0; i < 128; i++) {
    float d = signed_distance(hitPos);
    if (d >= 0) {
      Point3f dcopy = dir;
      dcopy.scale(std::max(d * 0.1f, .01f));
      hitPos.add(&dcopy);
      continue;
    }

    const float eps = 0.1;

    Point3f dx = Point3f(eps, 0, 0);
    dx.add(&hitPos);

    Point3f dy = Point3f(0, eps, 0);
    dy.add(&hitPos);

    Point3f dz = Point3f(0, 0, eps);
    dz.add(&hitPos);

    float nx = signed_distance(dx) - d;
    float ny = signed_distance(dy) - d;
    float nz = signed_distance(dz) - d;

    if (d < 0) {
      // compute parameter t, given a intersction point with a ray
      float t = (hitPos.x - ray->origin->x) / ray->direction->x;
      Point3f* norm = new Point3f(nx, ny, nz);
      norm->normalize();
      Point3f* wIn = new Point3f(ray->direction);
      wIn->negate();
      wIn->normalize();
      return new HitRecord (
        t,
        new Point3f(hitPos),
        norm,
        new Point3f(),
        wIn,
        material,
        this
      );
    }
  }
  return new HitRecord();
}

float Explosion::signed_distance(const Point3f& p) const { // this function defines the implicit surface we render
  Point3f q(p);
  q.scale(3.4);
  float noise_amplitude = 1.0;
  float displacement = -fractal_brownian_motion(&q) * noise_amplitude;
  return p.norm() - (radius + displacement);
}

Point3f Explosion::rotate(const Point3f& v) const {
  Point3f p(
    Point3f(0.00,  0.80,  0.60).dot(&v),
    Point3f(-0.80,  0.36, -0.48).dot(&v),
    Point3f(-0.60, -0.48,  0.64).dot(&v)
  );
  return p;
}

float Explosion::noise(const Point3f& x) const {
  Point3f p = Point3f(floor(x.x), floor(x.y), floor(x.z));
  Point3f f = Point3f(x.x - p.x, x.y - p.y, x.z - p.z);

  Point3f ff = Point3f(f);
  ff.scale(2);

  Point3f fff = Point3f(3.f, 3.f, 3.f);
  fff.sub(&ff);

  Point3f ffff = new Point3f(f.x * fff.x, f.y * fff.y, f.z * fff.z);
  Point3f f5(f.x * ffff.x, f.y * ffff.y, f.z * ffff.z);

  Point3f tmp(1.f, 57.f, 113.f);
  float n = p.dot(&tmp);
  return lerp(lerp(
        lerp(hash(n +  0.f), hash(n +  1.f), f5.x),
        lerp(hash(n + 57.f), hash(n + 58.f), f5.x), f5.y),
      lerp(
        lerp(hash(n + 113.f), hash(n + 114.f), f5.x),
        lerp(hash(n + 170.f), hash(n + 171.f), f5.x), f5.y), f5.z);
}

float Explosion::fractal_brownian_motion(const Point3f& x) const {
    Point3f p = rotate(x);
    float f = 0;
    f += 0.5000 * noise(p); p.scale(2.32);
    f += 0.2500 * noise(p); p.scale(3.03);
    f += 0.1250 * noise(p); p.scale(2.61);
    f += 0.0625 * noise(p);
    return f / 0.9375;
}
