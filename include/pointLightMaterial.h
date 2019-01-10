#include "material.h"
#include "point3f.h"
#include "spectrum.h"
#include "hitRecord.h"

#ifndef POINT_LIGHT_MATERIAL_H
#define POINT_LIGHT_MATERIAL_H

class PointLightMaterial : Material {
  public:
    Spectrum* emission;

    PointLightMaterial(Spectrum*);
    Spectrum* evaluateBrdf(HitRecord* hitRecord, Point3f* wOut, Point3f* wIn);
    Spectrum* evaluateEmission(HitRecord* hitRecord, Point3f* wOut);

    bool hasSpecularReflection();
    bool hasSpecularRefraction();
    bool castsShadows();
};

#endif
