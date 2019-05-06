#include "intersectables/containers/instance.h"

#include <memory>
#include "math/vector4f.h"

Instance::Instance(Intersectable* intersectable)
    : intersectable(intersectable),
      transformation(Matrix4f().eye()),
      aabb(intersectable->getBoundingBox()) {
  this->invTransformation = Matrix4f().eye();
  this->invTrasnposedTransformation = Matrix4f().eye();
}

Instance::Instance(Intersectable* intersectable, Matrix4f* transformation)
    : intersectable(intersectable),
      transformation(transformation),
      aabb(intersectable->getBoundingBox().transform(*transformation)) {
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

const BoundingBox& Instance::getBoundingBox() const { return aabb; }
