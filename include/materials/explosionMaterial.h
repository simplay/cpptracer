#ifndef EXPLOSION_MATERIAL_H
#define EXPLOSION_MATERIAL_H

#include <algorithm>
#include "../hitRecord.h"
#include "../math/vector3f.h"
#include "../spectrum.h"
#include "material.h"

class ExplosionMaterial : public Material {
 private:
  const Spectrum diffuseContribution;
  const Spectrum specularContribution;
  float shinynessPower;

  Spectrum lerp(Spectrum s0, Spectrum s1, float t) const {
    s1.add(s0);
    float scale = std::max(0.f, std::min(1.f, t));
    s1.scale(scale);
    s0.add(s1);
    return s0;
  }

 public:
  ExplosionMaterial(Spectrum*, Spectrum*, float);

  Spectrum* evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn) const override;
  Spectrum* evaluateEmission(HitRecord* hitRecord, Vector3f* wOut) const override;

  bool hasSpecularReflection() const override;
  bool hasSpecularRefraction() const override;
  bool castsShadows() const override;

  ShadingSample evaluateSpecularReflection(HitRecord* hitRecord) const override;
  ShadingSample evaluateSpecularRefraction(HitRecord* hitRecord) const override;
};
#endif
