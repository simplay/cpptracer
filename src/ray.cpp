#include "ray.h"
#include "math/point3f.h"

Ray::Ray(): origin(new Point3f()), direction(new Point3f()), t(0), depth(0) {}
Ray::Ray(Point3f* origin, Point3f* direction, float t):  direction(direction), t(t), depth(0) {
  Point3f* o = new Point3f(direction);
  o->scale(0.00001);
  o->add(origin);
  this->origin = origin;
}

Ray::Ray(Point3f* origin, Point3f* direction, float t, int depth):  direction(direction), t(t), depth(depth) {
  Point3f* o = new Point3f(direction);
  o->scale(0.00001);
  o->add(origin);
  this->origin = origin;
}

Point3f* Ray::pointAt(float t) {
  Point3f* p = new Point3f(*direction);
  p->scale(t);
  p->add(origin);
  return p;
}
