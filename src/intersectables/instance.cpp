#include "../math/vector4f.h"
#include "instance.h"

Instance::Instance(Intersectable* intersectable)
  : intersectable(intersectable), transformation(Matrix4f().eye()) {
    this->invTransformation = Matrix4f().eye();
    this->invTrasnposedTransformation = Matrix4f().eye();
}

Instance::Instance(Intersectable* intersectable, Matrix4f* transformation)
  : intersectable(intersectable), transformation(transformation) {
    this->invTransformation = transformation->inv();
    this->invTrasnposedTransformation = invTransformation->transposed();
}

Instance::~Instance() {
  delete transformation;
  delete invTransformation;
  delete invTrasnposedTransformation;
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

  // transform back
  Vector4f backHitPos(hit->position, 1);
  auto hitPos = transformation->mult(&backHitPos);
  auto hit3fPos = hitPos->toPoint3f();
  delete hitPos;

  Vector4f backHitNormal(hit->normal, 0);
  auto hitNormal = invTrasnposedTransformation->mult(&backHitNormal);
  auto hit3fNormal = hitNormal->toPoint3f();
  hit3fNormal->normalize();
  delete hitNormal;

  Vector4f backHitTangent(hit->tangent, 0);
  auto hitTangent = invTrasnposedTransformation->mult(&backHitTangent);
  auto hit3fTangent = hitTangent->toPoint3f();
  hit3fTangent->normalize();
  delete hitTangent;

  Vector4f backWIn(hit->wIn, 0);
  auto hitWIn = transformation->mult(&backWIn);
  auto hit3fWIn = hitWIn->toPoint3f();
  hit3fWIn->normalize();

  HitRecord* finalHit = new HitRecord(
    hit->t, // TODO: transform too
    hit3fPos,
    hit3fNormal,
    hit3fTangent,
    hit3fWIn,
    0,
    0
  );

  return finalHit;
}
