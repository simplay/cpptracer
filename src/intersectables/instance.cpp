#include "intersectables/instance.h"

#include <memory>
#include "math/vector4f.h"

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

HitRecord* Instance::intersect(const Ray& ray) const {
  auto transRay = std::unique_ptr<Ray>(ray.transform(invTransformation));

  auto hit = intersectable->intersect(*transRay);
  if (!hit->isValid()) {
    return hit;
  }

  auto finalHit = hit->transform(transformation, invTrasnposedTransformation);
  delete hit;

  return finalHit;
}
