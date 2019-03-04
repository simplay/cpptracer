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

HitRecord* Instance::intersect(Ray* ray) const {
  auto transRay = ray->transform(invTransformation);

  auto hit = intersectable->intersect(transRay);
  delete transRay;
  if (!hit->isValid()) {
    return hit;
  }

  auto finalHit = hit->transform(transformation, invTrasnposedTransformation);
  delete hit;

  return finalHit;
}
