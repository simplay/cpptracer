#include "hitRecord.h"

HitRecord::~HitRecord() {
  delete position;
  delete normal;
  delete tangent;
  delete wIn;
}

HitRecord::HitRecord() {
  isNull = true;
}

HitRecord::HitRecord(
  Point3f* position,
  Material* material
):
  position(position),
  normal(new Point3f()),
  tangent(new Point3f()),
  wIn(new Point3f()),
  material(material)
{};

HitRecord::HitRecord(
  float t,
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

HitRecord::HitRecord(
  float t,
  Point3f* position,
  Point3f* normal,
  Point3f* tangent,
  Point3f* wIn,
  Material* material,
  Intersectable *intersectable,
  int i,
  int j
):
  t(t),
  position(position),
  normal(normal),
  tangent(tangent),
  wIn(wIn),
  material(material),
  intersectable(intersectable),
  i(i),
  j(j)
{}

bool HitRecord::isValid() {
  return !isNull;
}
