#include <cmath>
#include <iostream>
#include "gridTexturedMaterial.h"

GridTexturedMaterial::GridTexturedMaterial(
  Spectrum* lineColor,
  Spectrum* tileColor,
  float thickness,
  Point3f* shift,
  float scale
): lineColor(lineColor),
  tileColor(tileColor),
  thickness(thickness),
  shift(shift),
  scale(scale),
  diffuse(new Diffuse(new Spectrum(1)))
{
}

Spectrum* GridTexturedMaterial::evaluateBrdf(HitRecord* hitRecord, Point3f* wOut, Point3f* wIn) {
  Spectrum* diffuseBRDF = diffuse->evaluateBrdf(hitRecord, wOut, wIn);

  Point3f* hitPoint = new Point3f(hitRecord->position);

  Point3f* shifted = new Point3f(hitRecord->position);
  shifted->add(shift);

  hitPoint->scale(1.0 / scale);
  shifted->scale(1.0 / scale);
  float relativeThickness = thickness / scale;

  Point3f* roundedPosition = new Point3f(
    std::round(hitPoint->x),
    std::round(hitPoint->y),
    std::round(hitPoint->z)
  );

  shifted->sub(roundedPosition);
  shifted->abs();

  if (shifted->x < relativeThickness ||
      shifted->y < relativeThickness ||
      shifted->z < relativeThickness)
    diffuseBRDF->mult(lineColor);
  else
    diffuseBRDF->mult(tileColor);

  return diffuseBRDF;
}

Spectrum* GridTexturedMaterial::evaluateEmission(HitRecord* hitRecord, Point3f* wIn) {
  return diffuse->evaluateEmission(hitRecord, wIn);
}

bool GridTexturedMaterial::hasSpecularReflection() {
  return diffuse->hasSpecularReflection();
}

bool GridTexturedMaterial::hasSpecularRefraction() {
  return diffuse->hasSpecularRefraction();
}

bool GridTexturedMaterial::castsShadows() {
  return diffuse->castsShadows();
}

ShadingSample* GridTexturedMaterial::evaluateSpecularReflection(HitRecord* hitRecord) {
  return diffuse->evaluateSpecularReflection(hitRecord);
}

ShadingSample* GridTexturedMaterial::evaluateSpecularRefraction(HitRecord* hitRecord) {
  return diffuse->evaluateSpecularRefraction(hitRecord);
}
