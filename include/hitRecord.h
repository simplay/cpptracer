#include <iostream>
#include "math/matrix4f.h"
#include "math/vector3f.h"

// forward declaration:
// See https://stackoverflow.com/questions/4757565/what-are-forward-declarations-in-c
class Material;
class Intersectable;

#ifndef HIT_RECORD_H
#define HIT_RECORD_H

// Stores information about a ray-surface intersection. This information is
// typically used for shading.
class HitRecord {
  private:

    // by default, a HitRecord is valid
    bool isNull = false;

  public:
    // ray parameter that resulted in a hit with a surface of an intersectable
    float t;

    // position where the ray hit the surface
    Vector3f* position;

    // normal at hit position
    Vector3f* normal;

    // tangent at hit position
    Vector3f* tangent;

    // Direction towards origin of ray that hit surface. By convention it
    // points away from the surface, that is, in the direction opposite to the
    // incident ray.
    Vector3f* wIn;

    // The material at the hit point.
    Material* material;

    const Intersectable* intersectable;

    // indices of ray that caused the intersection
    int i;
    int j;

    // the null-hitrecord
    ~HitRecord();
    HitRecord();

    HitRecord(HitRecord*);

    HitRecord(
      float t,
      Vector3f* position,
      Vector3f* normal,
      Vector3f* tangent,
      Vector3f* wIn,
      Material* material,
      const Intersectable* intersectable
    );

    HitRecord(
      float t,
      Vector3f* position,
      Vector3f* normal,
      Vector3f* tangent,
      Vector3f* wIn,
      Material* material,
      const Intersectable* intersectable,
      int i,
      int j
    );

    HitRecord(
      Vector3f* position,
      Material* material
    );

    // HitRecord objects are marked as invalid return true Used to avoid
    // null-checks
    bool isValid();

    HitRecord* transform(Matrix4f*, Matrix4f*);

    void log() {
      std::cout << t << std::endl;
      position->log();
      normal->log();
      tangent->log();
      wIn->log();
    }
};

#endif
