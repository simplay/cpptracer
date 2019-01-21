#include "point3f.h"
#include "spectrum.h"
#include "hitRecord.h"

#ifndef IMATERIAL_H
#define IMATERIAL_H

class Material {
  public:
    virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Point3f* wOut, Point3f* wIn) = 0;
    virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Point3f* wOut) = 0;

    virtual bool hasSpecularReflection() = 0;
    virtual bool hasSpecularRefraction() = 0;
    virtual bool castsShadows() = 0;
};
#endif
