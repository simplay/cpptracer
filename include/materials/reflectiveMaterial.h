#include <algorithm>
#include "material.h"
#include "../math/point3f.h"
#include "../spectrum.h"
#include "../hitRecord.h"

#ifndef REFLECTIVE_MATERIAL_H
#define REFLECTIVE_MATERIAL_H

class ReflectiveMaterial : public Material {
  public:
    Spectrum* ks;

    ReflectiveMaterial();
    ReflectiveMaterial(Spectrum*);

    virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Point3f* wOut, Point3f* wIn);
    virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Point3f* wOut);

    virtual bool hasSpecularReflection();
    virtual bool hasSpecularRefraction();
    virtual bool castsShadows();
    virtual ShadingSample* evaluateSpecularReflection(HitRecord* hitRecord);
};
#endif
