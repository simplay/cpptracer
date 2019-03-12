#ifndef BLINN_H
#define BLINN_H

#include "material.h"

class Blinn : public Material {
 private:
  const Spectrum diffuseContribution;
  const Spectrum specularContribution;
  const float shinynessPower;

 public:
  Blinn(Spectrum*, Spectrum*, float);
  virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn);
  virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Vector3f* wOut);

  virtual bool hasSpecularReflection();
  virtual bool hasSpecularRefraction();
  virtual bool castsShadows();
  virtual ShadingSample* evaluateSpecularReflection(HitRecord* hitRecord);
  virtual ShadingSample* evaluateSpecularRefraction(HitRecord* hitRecord);
};
#endif
