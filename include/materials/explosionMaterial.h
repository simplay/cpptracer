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

  virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn);
  virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Vector3f* wOut);

  virtual bool hasSpecularReflection();
  virtual bool hasSpecularRefraction();
  virtual bool castsShadows();

  virtual ShadingSample* evaluateSpecularReflection(HitRecord* hitRecord);
  virtual ShadingSample* evaluateSpecularRefraction(HitRecord* hitRecord);
};
#endif
