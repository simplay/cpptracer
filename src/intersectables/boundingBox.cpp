#include "boundingBox.h"

BoundingBox::BoundingBox(const Vector3f& bottomLeft, const Vector3f& topRight)
    : bottomLeft(bottomLeft), topRight(topRight) {}
HitRecord* BoundingBox::intersect(const Ray& ray) const { return new HitRecord(); }
