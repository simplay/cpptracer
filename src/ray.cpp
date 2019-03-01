#include <iostream>
#include "ray.h"
#include "math/point3f.h"

Ray::~Ray() {
  // TODO implement me, cannot yet delete origin and direction
}

Ray::Ray(Point3f* origin, Point3f* direction, bool perturbate)
  : origin(origin), direction(direction), depth(0), i(-1), j(-1) {
    if (perturbate) {
      Point3f* o = new Point3f(direction);
      o->scale(EPSILON);
      o->add(origin);
      delete origin;
      this->origin = o;
    }
}

Ray::Ray(Point3f* origin, Point3f* direction, int i, int j, bool perturbate)
  : origin(origin), direction(direction), depth(0), i(i), j(j) {
    if (perturbate) {
      Point3f* o = new Point3f(direction);
      o->scale(EPSILON);
      o->add(origin);
      delete origin;
      this->origin = o;
    }
}

Ray::Ray(Point3f* origin, Point3f* direction, int depth, bool perturbate)
  : origin(origin), direction(direction), depth(depth), i(-1), j(-1) {
    if (perturbate) {
      Point3f* o = new Point3f(direction);
      o->scale(EPSILON);
      o->add(origin);
      delete origin;
      this->origin = o;
    }
}

Point3f* Ray::pointAt(float t) {
  Point3f* hit = new Point3f(direction);
  hit->scaleAdd(t, origin);
  return hit;
}

Ray* Ray::transform(Matrix4f* invT) {
  Vector4f orig(origin, 1);
  auto transRayOrig = invT->mult(&orig);

  Vector4f dir(direction, 0);
  auto transRayDir = invT->mult(&dir);

  Ray* transRay = new Ray(
    new Point3f(transRayOrig), new Point3f(transRayDir)
  );
  delete transRayOrig;
  delete transRayDir;

  return transRay;
}
