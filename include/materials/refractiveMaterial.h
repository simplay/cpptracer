#ifndef REFRACTIVE_MATERIAL_H
#define REFRACTIVE_MATERIAL_H

#include <algorithm>
#include "../hitRecord.h"
#include "../math/vector3f.h"
#include "../spectrum.h"
#include "material.h"

class RefractiveMaterial : public Material {
 private:
  // based on Schlick's approximation:
  // See https://en.wikipedia.org/wiki/Schlick%27s_approximation
  float fresnelFactor(HitRecord*) const;

  const float refractionIndex;
  const Spectrum ks;

 public:
  RefractiveMaterial(float);
  RefractiveMaterial(float, Spectrum*);

  Spectrum* evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn) const override;
  Spectrum* evaluateEmission(HitRecord* hitRecord, Vector3f* wOut) const override;

  bool hasSpecularReflection() const override;
  bool hasSpecularRefraction() const override;
  bool castsShadows() const override;

  ShadingSample evaluateSpecularReflection(HitRecord* hitRecord) const override;
  ShadingSample evaluateSpecularRefraction(HitRecord* hitRecord) const override;
};
#endif
