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
  Spectrum evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn) const override;
  Spectrum evaluateEmission(HitRecord* hitRecord, Vector3f* wOut) const override;

  bool hasSpecularReflection() const override;
  bool hasSpecularRefraction() const override;
  bool castsShadows() const override;
  ShadingSample evaluateSpecularReflection(HitRecord* hitRecord) const override;
  ShadingSample evaluateSpecularRefraction(HitRecord* hitRecord) const override;
};
#endif
