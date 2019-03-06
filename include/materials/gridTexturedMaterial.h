#include "diffuse.h"
#include "../math/vector3f.h"
#include "../spectrum.h"
#include "../hitRecord.h"

#ifndef GRID_TEXTURED_MATERIAL_H
#define GRID_TEXTURED_MATERIAL_H

class GridTexturedMaterial : public Material {
  public:
    Spectrum* lineColor;
    Spectrum* tileColor;
    float thickness;
    Vector3f* shift;
    float scale;
    Diffuse* diffuse;

    GridTexturedMaterial(Spectrum* lineColor, Spectrum* tileColor, float thickness, Vector3f* shift, float scale);
    virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn);
    virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Vector3f* wOut);

    virtual bool hasSpecularReflection();
    virtual bool hasSpecularRefraction();
    virtual bool castsShadows();
    virtual ShadingSample* evaluateSpecularReflection(HitRecord* hitRecord);
    virtual ShadingSample* evaluateSpecularRefraction(HitRecord* hitRecord);
};
#endif
