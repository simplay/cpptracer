#include "hitRecord.h"

HitRecord::HitRecord() {
  isNull = true;
}

HitRecord::HitRecord(
  Point3f* position,
  Material* material
):
  position(position),
  material(material)
{};

HitRecord::HitRecord(
  float &t,
  Point3f* position,
  Point3f* normal,
  Point3f* tangent,
  Point3f* wIn,
  Material* material,
  Intersectable *intersectable
):
  t(t),
  position(position),
  normal(normal),
  tangent(tangent),
  wIn(wIn),
  material(material),
  intersectable(intersectable)
{}

bool HitRecord::isValid() {
  return !isNull;
}
