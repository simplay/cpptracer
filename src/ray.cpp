#include "ray.h"

#include <iostream>

#include "math/vector3f.h"

Ray::~Ray() {
  // TODO implement me, cannot yet delete origin and direction
}

Vector3f* Ray::perturbatedOrigin(Vector3f* oldOrigin, Vector3f* direction) {
  auto o = new Vector3f(*direction);
  o->scale(EPSILON);
  o->add(*oldOrigin);
  return o;
}

Ray::Ray(Vector3f* origin, Vector3f* direction, bool perturbate)
    : origin(perturbate ? perturbatedOrigin(origin, direction) : origin),
      direction(direction),
      depth(0),
      i(-1),
      j(-1) {}

Ray::Ray(Vector3f* origin, Vector3f* direction, int i, int j, bool perturbate)
    : origin(perturbate ? perturbatedOrigin(origin, direction) : origin),
      direction(direction),
      depth(0),
      i(i),
      j(j) {}

Ray::Ray(Vector3f* origin, Vector3f* direction, int depth, bool perturbate)
    : origin(perturbate ? perturbatedOrigin(origin, direction) : origin),
      direction(direction),
      depth(depth),
      i(-1),
      j(-1) {}

Vector3f* Ray::pointAt(float t) const {
  Vector3f* hit = new Vector3f(*direction);
  hit->scaleAdd(t, *origin);
  return hit;
}

Ray* Ray::transform(Matrix4f* invT) const {
  Vector4f orig(*origin, 1);
  auto transRayOrig = invT->mult(orig);

  Vector4f dir(*direction, 0);
  auto transRayDir = invT->mult(dir);

  Ray* transRay = new Ray(new Vector3f(*transRayOrig), new Vector3f(*transRayDir));
  delete transRayOrig;
  delete transRayDir;

  return transRay;
}
