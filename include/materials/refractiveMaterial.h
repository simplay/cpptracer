#include <algorithm>
#include "material.h"
#include "../math/vector3f.h"
#include "../spectrum.h"
#include "../hitRecord.h"

#ifndef REFRACTIVE_MATERIAL_H
#define REFRACTIVE_MATERIAL_H

class RefractiveMaterial : public Material {
  private:
    // based on Schlick's approximation:
    // See https://en.wikipedia.org/wiki/Schlick%27s_approximation
    float fresnelFactor(HitRecord*);

    float refractionIndex;
    Spectrum* ks;

  public:
    RefractiveMaterial(float);
    RefractiveMaterial(float, Spectrum*);

    virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn);
    virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Vector3f* wOut);

    virtual bool hasSpecularReflection();
    virtual bool hasSpecularRefraction();
    virtual bool castsShadows();

    virtual ShadingSample* evaluateSpecularReflection(HitRecord* hitRecord);
    virtual ShadingSample* evaluateSpecularRefraction(HitRecord* hitRecord);
};
#endif

