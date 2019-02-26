#include "../math/vector4f.h"
#include "instance.h"

Instance::Instance(Intersectable* intersectable, Matrix4f* transformation)
  : intersectable(intersectable), transformation(transformation) {
    // TODO: compute inverse transformation here
    this->invTransformation = transformation;
}

HitRecord* Instance::intersect(Ray* ray) {
  Vector4f* orig = new Vector4f(ray->origin, 1);
  auto transRayOrig = invTransformation->mult(orig);
  delete orig;

  Vector4f* dir = new Vector4f(ray->direction, 0);
  auto transRayDir = invTransformation->mult(dir);
  delete dir;

  Ray* transRay = new Ray(
    new Point3f(transRayOrig), new Point3f(transRayDir)
  );
  delete transRayOrig;
  delete transRayDir;

  auto hit = intersectable->intersect(transRay);
  delete transRay;

  // TODO transform hit back using transformation
  return hit;
}
