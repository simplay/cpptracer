#include "material.h"
#include "../math/point3f.h"
#include "../spectrum.h"
#include "../hitRecord.h"

#ifndef POINT_LIGHT_MATERIAL_H
#define POINT_LIGHT_MATERIAL_H

class PointLightMaterial {
  public:
    Spectrum* emission;

    PointLightMaterial(Spectrum*);
    virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Point3f* wOut, Point3f* wIn);
    virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Point3f* wOut);

    virtual bool hasSpecularReflection();
    virtual bool hasSpecularRefraction();
    virtual bool castsShadows();
    virtual ShadingSample* evaluateSpecularReflection(HitRecord* hitRecord);
    virtual ShadingSample* evaluateSpecularRefraction(HitRecord* hitRecord);
};

#endif
