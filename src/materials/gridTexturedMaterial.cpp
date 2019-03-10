#include "materials/gridTexturedMaterial.h"
#include <cmath>
#include <iostream>

// TODO(panmari): Change constructor to only allow const ref. Currently, this is a memory leak.
GridTexturedMaterial::GridTexturedMaterial(Spectrum* lineColor, Spectrum* tileColor,
                                           float thickness, Vector3f* shift, float scale)
    : lineColor(*lineColor),
      tileColor(*tileColor),
      thickness(thickness),
      shift(shift),
      scale(scale),
      diffuse(new Spectrum(1)) {}

Spectrum* GridTexturedMaterial::evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn) {
  Spectrum* diffuseBRDF = diffuse.evaluateBrdf(hitRecord, wOut, wIn);

  Vector3f* hitPoint = new Vector3f(hitRecord->position);

  Vector3f* shifted = new Vector3f(hitRecord->position);
  shifted->add(&shift);

  hitPoint->scale(1.0 / scale);
  shifted->scale(1.0 / scale);
  float relativeThickness = thickness / scale;

  Vector3f* roundedPosition =
      new Vector3f(std::round(hitPoint->x), std::round(hitPoint->y), std::round(hitPoint->z));

  shifted->sub(roundedPosition);
  shifted->abs();

  if (shifted->x < relativeThickness || shifted->y < relativeThickness ||
      shifted->z < relativeThickness)
    diffuseBRDF->mult(lineColor);
  else
    diffuseBRDF->mult(tileColor);

  return diffuseBRDF;
}

Spectrum* GridTexturedMaterial::evaluateEmission(HitRecord* hitRecord, Vector3f* wIn) {
  return diffuse.evaluateEmission(hitRecord, wIn);
}

bool GridTexturedMaterial::hasSpecularReflection() { return diffuse.hasSpecularReflection(); }

bool GridTexturedMaterial::hasSpecularRefraction() { return diffuse.hasSpecularRefraction(); }

bool GridTexturedMaterial::castsShadows() { return diffuse.castsShadows(); }

ShadingSample* GridTexturedMaterial::evaluateSpecularReflection(HitRecord* hitRecord) {
  return diffuse.evaluateSpecularReflection(hitRecord);
}

ShadingSample* GridTexturedMaterial::evaluateSpecularRefraction(HitRecord* hitRecord) {
  return diffuse.evaluateSpecularRefraction(hitRecord);
}
