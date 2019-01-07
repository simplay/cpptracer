#include "ray.h"
#include "point3f.h"
#include <iostream>

Ray::Ray(): origin(new Point3f()), direction(new Point3f()), t(0) {}
Ray::Ray(Point3f* origin, Point3f* direction, float t): origin(origin), direction(direction), t(t) {}

Point3f Ray::pointAt(float t) {
  Point3f p(*direction);
  p.scale(t);
  p.add(origin);
  return p;
}

void Ray::debug() {
  origin->debug();
  direction->debug();
  std::cout << "t = " << t << std::endl;
}
