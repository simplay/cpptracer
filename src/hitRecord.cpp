#include "hitRecord.h"

HitRecord::HitRecord(
    float t,
    Point3f* position,
    Point3f* normal,
    Point3f* tangent,
    Point3f* wIn,
    Material* material,
    Point3f* w
): t(t), position(position), normal(normal), tangent(tangent), wIn(wIn), material(material), w(w)
{}
