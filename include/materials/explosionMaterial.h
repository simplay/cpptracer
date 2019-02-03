#include <algorithm>
#include "material.h"
#include "../math/point3f.h"
#include "../spectrum.h"
#include "../hitRecord.h"

#ifndef EXPLOSION_MATERIAL_H
#define EXPLOSION_MATERIAL_H

class ExplosionMaterial : public Material {
  public:
    Spectrum* diffuseContribution;
    Spectrum* specularContribution;
    float shinynessPower;

    ExplosionMaterial(Spectrum*, Spectrum*, float);

    virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Point3f* wOut, Point3f* wIn);
    virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Point3f* wOut);

    virtual bool hasSpecularReflection();
    virtual bool hasSpecularRefraction();
    virtual bool castsShadows();

    Spectrum* lerp(Spectrum* v0, Spectrum* v1, float t) {
      Spectrum s0(*v0);
      Spectrum s1(*v1);
      s1.add(&s0);
      float scale = std::max(0.f, std::min(1.f, t));
      s1.scale(scale);
      s0.add(&s1);
      return new Spectrum(s0.r, s0.g, s0.b);
    }
    virtual ShadingSample* evaluateSpecularReflection(HitRecord* hitRecord);
};
#endif
