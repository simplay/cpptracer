#include "point3f.h"
#include "material.h"

#ifndef HIT_RECORD_H
#define HIT_RECORD_H

// Stores information about a ray-surface intersection. This information
// is typically used for shading.
//
// position: Point3f
//   position where the ray hit the surface
//
// normal: Point3f
//   normal at hit pos
//
// tangent: Point3f
//   tangent at hit position
//
// w: Point3f
//   Direction towards origin of ray that hit surface.
//   By convention it points away from the surface,
//   that is, in the direction opposite to the incident ray.
//
// t: Float
//   parameter of the ray at the hit point
//
// material: Material
//   The material at the hit point.
class HitRecord {
  public:
    float t;
    Point3f* position;
    Point3f* normal;
    Point3f* tangent;
    Point3f* wIn;
    Material* material;
    Point3f* w;

    HitRecord(
      float t,
      Point3f* position,
      Point3f* normal,
      Point3f* tangent,
      Point3f* wIn,
      Material* material,
      Point3f* w
    );
};

#endif
