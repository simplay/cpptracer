#include <math.h>
#include <iostream>
#include "refractiveMaterial.h"

float RefractiveMaterial::fresnelFactor(HitRecord* hitRecord) {
  Point3f wIn(hitRecord->wIn);
  wIn.negate();
  wIn.normalize();

  Point3f normal(hitRecord->normal);

  // enters material
  float n1 = 1;
  float n2 = refractionIndex;

  // leaves material
  if (hitRecord->normal->dot(hitRecord->wIn) <= 0) {
    n1 = refractionIndex;
    n2 = 1;
    normal.negate();
  }

  float cosThetaI = -wIn.dot(&normal);
  float phaseVelocity = n1 / n2;

  float sin2ThetaT = pow(phaseVelocity, 2.0) * (1.0 - pow(cosThetaI, 2.0));
  if (sin2ThetaT > 1) {
    return 1;
  }

  float r0 = (n1 - n2) / (n1 + n2);
  r0 *= r0;

  if (n1 <= n2) {
    float x = 1.0 - cosThetaI;
    return r0 + (1.0 - r0) * pow(x, 5);
  } else {
    float cosThetaT = sqrt(1.0 - sin2ThetaT);
    float x = 1.0 - cosThetaT;
    return r0 + (1.0 - r0) * pow(x, 5);
  }
}

RefractiveMaterial::RefractiveMaterial(float refractionIndex)
  : refractionIndex(refractionIndex), ks(new Spectrum(1)) {}

RefractiveMaterial::RefractiveMaterial(float refractionIndex, Spectrum* ks)
  : refractionIndex(refractionIndex), ks(ks) {}

Spectrum* RefractiveMaterial::evaluateBrdf(HitRecord* hitRecord, Point3f* wOut, Point3f* wIn) {
  return new Spectrum();
}

Spectrum* RefractiveMaterial::evaluateEmission(HitRecord*, Point3f*) {
  return new Spectrum();
}

bool RefractiveMaterial::hasSpecularReflection() {
  return true;
}

bool RefractiveMaterial::hasSpecularRefraction() {
  return true;
}

bool RefractiveMaterial::castsShadows() {
  return false;
}

ShadingSample* RefractiveMaterial::evaluateSpecularReflection(HitRecord* hitRecord) {
  auto reflectedDir = hitRecord->wIn->invReflected(hitRecord->normal);
  float r = fresnelFactor(hitRecord);

  Spectrum* brdf = new Spectrum(r);
  ShadingSample* sample = new ShadingSample(
    brdf,
    new Spectrum(),
    reflectedDir,
    true,
    r
  );
  return sample;
}

ShadingSample* RefractiveMaterial::evaluateSpecularRefraction(HitRecord* hitRecord) {
  Point3f wIn(hitRecord->wIn);
  wIn.negate();
  wIn.normalize();

  Point3f normal(hitRecord->normal);

  // enters material
  float n1 = 1.0;
  float n2 = refractionIndex;

  // leaves material
  if (hitRecord->normal->dot(hitRecord->wIn) <= 0.0) {
    n1 = refractionIndex;
    n2 = 1.0;
    normal.negate();
  }

  float cosThetaI = -wIn.dot(&normal);
  float phaseVelocity = n1 / n2;
  float sin2ThetaT = pow(phaseVelocity, 2.0) * (1.0 - pow(cosThetaI, 2.0));
  if (sin2ThetaT > 1.0) {
    return new ShadingSample();
  }

  Point3f* refractedDir = new Point3f(wIn);
  refractedDir->scale(phaseVelocity);

  Point3f scaledNormal(normal);
  scaledNormal.scale(phaseVelocity * cosThetaI - sqrt(1.0 - sin2ThetaT));
  refractedDir->add(&scaledNormal);

  Spectrum* brdf = new Spectrum(ks);
  float r = fresnelFactor(hitRecord);
  brdf->scale(1.0 - r);

  ShadingSample* sample = new ShadingSample(
    brdf,
    new Spectrum(),
    refractedDir,
    true,
    r
  );

  return sample;
}
