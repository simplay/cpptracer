#ifndef REFLECTIVE_MATERIAL_H
#define REFLECTIVE_MATERIAL_H

#include <algorithm>
#include "../hitRecord.h"
#include "../math/vector3f.h"
#include "../spectrum.h"
#include "material.h"

class ReflectiveMaterial : public Material {
 private:
  const Spectrum ks;

 public:
  ReflectiveMaterial();
  ReflectiveMaterial(Spectrum*);

  virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn);
  virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Vector3f* wOut);

  virtual bool hasSpecularReflection();
  virtual bool hasSpecularRefraction();
  virtual bool castsShadows();

  ShadingSample evaluateSpecularReflection(HitRecord* hitRecord) const override;
  ShadingSample evaluateSpecularRefraction(HitRecord* hitRecord) const override;
};
#endif
