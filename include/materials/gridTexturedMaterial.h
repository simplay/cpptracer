#ifndef GRID_TEXTURED_MATERIAL_H
#define GRID_TEXTURED_MATERIAL_H

#include "../hitRecord.h"
#include "../math/vector3f.h"
#include "../spectrum.h"
#include "diffuse.h"

class GridTexturedMaterial : public Material {
 private:
  const Spectrum lineColor;
  const Spectrum tileColor;
  const float thickness;
  const Vector3f shift;
  const float scale;
  Diffuse diffuse;

 public:
  GridTexturedMaterial(Spectrum* lineColor, Spectrum* tileColor, float thickness, Vector3f* shift,
                       float scale);

  Spectrum* evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn) const override;
  Spectrum* evaluateEmission(HitRecord* hitRecord, Vector3f* wOut) const override;

  bool hasSpecularReflection() const override;
  bool hasSpecularRefraction() const override;
  bool castsShadows() const override;

  ShadingSample evaluateSpecularReflection(HitRecord* hitRecord) const override;
  ShadingSample evaluateSpecularRefraction(HitRecord* hitRecord) const override;
};
#endif
