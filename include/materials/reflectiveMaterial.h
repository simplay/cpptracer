#include <algorithm>
#include "material.h"
#include "../math/vector3f.h"
#include "../spectrum.h"
#include "../hitRecord.h"

#ifndef REFLECTIVE_MATERIAL_H
#define REFLECTIVE_MATERIAL_H

class ReflectiveMaterial : public Material {
  private:
    Spectrum* ks;

  public:
    ReflectiveMaterial();
    ReflectiveMaterial(Spectrum*);

    virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn);
    virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Vector3f* wOut);

    virtual bool hasSpecularReflection();
    virtual bool hasSpecularRefraction();
    virtual bool castsShadows();

    virtual ShadingSample* evaluateSpecularReflection(HitRecord* hitRecord);
    virtual ShadingSample* evaluateSpecularRefraction(HitRecord* hitRecord);
};
#endif
