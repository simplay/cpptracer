#include "math/point3f.h"

// forward declaration:
// See https://stackoverflow.com/questions/4757565/what-are-forward-declarations-in-c
class Material;
class Intersectable;

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
  private:
    // by default, a HitRecord is valid
    bool isNull = false;

  public:
    float epsilon = 0.000001;
    float t;
    Point3f* position;
    Point3f* normal;
    Point3f* tangent;
    Point3f* wIn;
    Material* material;
    Intersectable* intersectable;

    // the null-hitrecord
    HitRecord();

    HitRecord(
      float &t,
      Point3f* position,
      Point3f* normal,
      Point3f* tangent,
      Point3f* wIn,
      Material* material,
      Intersectable* intersectable
    );

    HitRecord(
      Point3f* position,
      Material* material
    );

    // HitRecord objects are marked as invalid return true
    // Used to avoid null-checks
    bool isValid();
};

#endif
