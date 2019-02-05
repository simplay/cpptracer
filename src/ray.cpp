#include "ray.h"
#include "math/point3f.h"

Ray::Ray(): origin(new Point3f()), direction(new Point3f()), depth(0) {}
Ray::Ray(Point3f* origin, Point3f* direction):  direction(direction), depth(0) {
  Point3f* o = new Point3f(direction);
  o->scale(0.00001);
  o->add(origin);
  this->origin = origin;
}

Ray::Ray(Point3f* origin, Point3f* direction, int depth):  direction(direction), depth(depth) {
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
