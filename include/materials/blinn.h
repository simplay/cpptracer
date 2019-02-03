#include "material.h"

#ifndef BLINN_H
#define BLINN_H
class Blinn : public Material {
  public:
    Spectrum* diffuseContribution;
    Spectrum* specularContribution;
    float shinynessPower;

    Blinn(Spectrum*, Spectrum*, float);
    virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Point3f* wOut, Point3f* wIn);
    virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Point3f* wOut);

    virtual bool hasSpecularReflection();
    virtual bool hasSpecularRefraction();
    virtual bool castsShadows();
    virtual ShadingSample* evaluateSpecularReflection(HitRecord* hitRecord);
};
#endif
