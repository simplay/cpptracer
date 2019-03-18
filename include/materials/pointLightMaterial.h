#ifndef POINT_LIGHT_MATERIAL_H
#define POINT_LIGHT_MATERIAL_H

#include "../hitRecord.h"
#include "../math/vector3f.h"
#include "../spectrum.h"
#include "material.h"

class PointLightMaterial : public Material {
 private:
  const Spectrum emission;

 public:
  PointLightMaterial(Spectrum*);
  Spectrum* evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn) const override;
  Spectrum* evaluateEmission(HitRecord* hitRecord, Vector3f* wOut) const override;

  bool hasSpecularReflection() const override;
  bool hasSpecularRefraction() const override;
  bool castsShadows() const override;
  ShadingSample evaluateSpecularReflection(HitRecord* hitRecord) const override;
  ShadingSample evaluateSpecularRefraction(HitRecord* hitRecord) const override;
};
#endif
