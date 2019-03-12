#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "../hitRecord.h"
#include "../math/vector3f.h"
#include "../spectrum.h"
#include "material.h"

class Diffuse : public Material {
 private:
  Spectrum emission;

 public:
  Diffuse(const Spectrum*);
  virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn);
  virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Vector3f* wOut);

  virtual bool hasSpecularReflection();
  virtual bool hasSpecularRefraction();
  virtual bool castsShadows();
  virtual ShadingSample* evaluateSpecularReflection(HitRecord* hitRecord);
  virtual ShadingSample* evaluateSpecularRefraction(HitRecord* hitRecord);
};
#endif
