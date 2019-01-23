#include "material.h"
#include "../math/point3f.h"
#include "../spectrum.h"
#include "../hitRecord.h"

#ifndef DIFFUSE_H
#define DIFFUSE_H

class Diffuse : public Material {
  public:
    Spectrum* emission;

    Diffuse(Spectrum*);
    virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Point3f* wOut, Point3f* wIn);
    virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Point3f* wOut);

    virtual bool hasSpecularReflection();
    virtual bool hasSpecularRefraction();
    virtual bool castsShadows();

};
#endif
