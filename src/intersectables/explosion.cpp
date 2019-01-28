#include <iostream>
#include <cmath>
#include "explosion.h"

Explosion::Explosion(Material* material, Point3f* center, float radius)
  : material(material), center(center), radius(radius)
{}

HitRecord* Explosion::intersect(Ray* ray) {
  Point3f* orig = new Point3f(ray->origin);
  Point3f* dir = new Point3f(ray->direction);
  if (orig->dot() - pow(orig->dot(dir), 2) > pow(radius, 2)) {
    return new HitRecord();
  }

  Point3f* hitPos = new Point3f(orig);
  for (size_t i = 0; i < 128; i++) {
    float d = signed_distance(hitPos);
    Point3f* wIn = new Point3f(ray->direction);
    wIn->negate();
    wIn->normalize();

    const float eps = 0.1;

    Point3f* dx = new Point3f(eps, 0, 0);
    dx->add(hitPos);

    Point3f* dy = new Point3f(0, eps, 0);
    dx->add(hitPos);

    Point3f* dz = new Point3f(0, 0, eps);
    dx->add(hitPos);

    float nx = signed_distance(dx) - d;
    float ny = signed_distance(dy) - d;
    float nz = signed_distance(dz) - d;

    Point3f* norm = new Point3f(nx, ny, nz);
    norm->normalize();

    // compute parameter t, given a intersction point with a ray
    float t = (hitPos->x - ray->origin->x) / ray->direction->x;
    if (d < 0) {
      return new HitRecord (
        t,
        hitPos,
        norm,
        NULL,
        wIn,
        material,
        this
      );
    }
    Point3f* dcopy = new Point3f(dir);
    dcopy->scale(std::max(d * 0.1f, .01f));
    hitPos->add(dcopy);
  }
  return new HitRecord();
}

float Explosion::signed_distance(Point3f* p) { // this function defines the implicit surface we render
  Point3f* q = new Point3f(p);
  q->scale(3.4);
  float noise_amplitude = 2.0;
  float displacement = -fractal_brownian_motion(q) * noise_amplitude;
  return p->norm() - (radius + displacement);
}

Point3f* Explosion::rotate(Point3f* v) {
  return new Point3f(
    Point3f(0.00,  0.80,  0.60).dot(v),
    Point3f(-0.80,  0.36, -0.48).dot(v),
    Point3f(-0.60, -0.48,  0.64).dot(v)
  );
}

float Explosion::noise(Point3f* x) {
  Point3f* p = new Point3f(floor(x->x), floor(x->y), floor(x->z));
  Point3f* f = new Point3f(x->x - p->x, x->y - p->y, x->z - p->z);

  Point3f* ff = new Point3f(f);
  ff->scale(2);

  Point3f* fff = new Point3f(3.f, 3.f, 3.f);
  fff->sub(ff);

  Point3f* ffff = new Point3f(f->x * fff->x, f->y * fff->y, f->z * fff->z);
  Point3f* f5 = new Point3f(f->x * ffff->x, f->y * ffff->y, f->z * ffff->z);

  f = f5;

  float n = p->dot(new Point3f(1.f, 57.f, 113.f));
  return lerp(lerp(
        lerp(hash(n +  0.f), hash(n +  1.f), f->x),
        lerp(hash(n + 57.f), hash(n + 58.f), f->x), f->y),
      lerp(
        lerp(hash(n + 113.f), hash(n + 114.f), f->x),
        lerp(hash(n + 170.f), hash(n + 171.f), f->x), f->y), f->z);
}

float Explosion::fractal_brownian_motion(Point3f* x) {
    Point3f* p = rotate(x);
    float f = 0;
    f += 0.5000 * noise(p); p->scale(2.32);
    f += 0.2500 * noise(p); p->scale(3.03);
    f += 0.1250 * noise(p); p->scale(2.61);
    f += 0.0625 * noise(p);
    return f / 0.9375;
}
