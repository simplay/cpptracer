#include <iostream>
#include "ray.h"
#include "math/vector3f.h"

Ray::~Ray() {
  // TODO implement me, cannot yet delete origin and direction
}

Ray::Ray(Vector3f* origin, Vector3f* direction, bool perturbate)
  : origin(origin), direction(direction), depth(0), i(-1), j(-1) {
    if (perturbate) {
      Vector3f* o = new Vector3f(direction);
      o->scale(EPSILON);
      o->add(origin);
      delete origin;
      this->origin = o;
    }
}

Ray::Ray(Vector3f* origin, Vector3f* direction, int i, int j, bool perturbate)
  : origin(origin), direction(direction), depth(0), i(i), j(j) {
    if (perturbate) {
      Vector3f* o = new Vector3f(direction);
      o->scale(EPSILON);
      o->add(origin);
      delete origin;
      this->origin = o;
    }
}

Ray::Ray(Vector3f* origin, Vector3f* direction, int depth, bool perturbate)
  : origin(origin), direction(direction), depth(depth), i(-1), j(-1) {
    if (perturbate) {
      Vector3f* o = new Vector3f(direction);
      o->scale(EPSILON);
      o->add(origin);
      delete origin;
      this->origin = o;
    }
}

Vector3f* Ray::pointAt(float t) {
  Vector3f* hit = new Vector3f(direction);
  hit->scaleAdd(t, origin);
  return hit;
}

Ray* Ray::transform(Matrix4f* invT) {
  Vector4f orig(origin, 1);
  auto transRayOrig = invT->mult(&orig);

  Vector4f dir(direction, 0);
  auto transRayDir = invT->mult(&dir);

  Ray* transRay = new Ray(
    new Vector3f(transRayOrig), new Vector3f(transRayDir)
  );
  delete transRayOrig;
  delete transRayDir;

  return transRay;
}
