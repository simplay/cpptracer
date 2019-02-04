#include "diffuse.h"
#include "../math/point3f.h"
#include "../spectrum.h"
#include "../hitRecord.h"

#ifndef GRID_TEXTURED_MATERIAL_H
#define GRID_TEXTURED_MATERIAL_H

class GridTexturedMaterial : public Material {
  public:
    float scale;
    float thickness;
    Point3f* shift;
    Spectrum* lineColor;
    Spectrum* tileColor;
    Diffuse* diffuse;

    GridTexturedMaterial(Spectrum* lineColor, Spectrum* tileColor, float thickness, Point3f* shift, float scale);
    virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Point3f* wOut, Point3f* wIn);
    virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Point3f* wOut);

    virtual bool hasSpecularReflection();
    virtual bool hasSpecularRefraction();
    virtual bool castsShadows();
    virtual ShadingSample* evaluateSpecularReflection(HitRecord* hitRecord);
    virtual ShadingSample* evaluateSpecularRefraction(HitRecord* hitRecord);
};
#endif
