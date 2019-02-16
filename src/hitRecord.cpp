#include "hitRecord.h"

HitRecord::~HitRecord() {
  delete position;
  delete normal;
  delete tangent;
  delete wIn;
}

HitRecord::HitRecord()
  :
    t(0),
    position(new Point3f()),
    normal(new Point3f()),
    tangent(new Point3f()),
    wIn(new Point3f())
{
  isNull = true;
}

HitRecord::HitRecord(HitRecord* hitRecord)
  :
    t(hitRecord->t),
    position(new Point3f(hitRecord->position)),
    normal(new Point3f(hitRecord->normal)),
    tangent(new Point3f(hitRecord->tangent)),
    wIn(new Point3f(hitRecord->wIn)),
    material(hitRecord->material),
    i(hitRecord->i),
    j(hitRecord->j)
{
  this->isNull = !hitRecord->isValid();
}

HitRecord::HitRecord(
  Point3f* position,
  Material* material
):
  t(0),
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
