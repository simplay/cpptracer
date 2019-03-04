#include "../intersectables/lightGeometry.h"
#include "../spectrum.h"

class Material;

#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

class PointLight : public LightGeometry {
  public:
    Point3f* position;
    Material* material;

    PointLight(Point3f*, Spectrum*);
    virtual HitRecord* sample() const;
    virtual HitRecord* intersect(Ray*) const;
};
#endif
