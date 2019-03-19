#include "materials/refractiveMaterial.h"
#include <math.h>
#include <iostream>

float RefractiveMaterial::fresnelFactor(HitRecord* hitRecord) const {
  Vector3f wIn(*hitRecord->wIn);
  wIn.negate();
  wIn.normalize();

  Vector3f normal(*hitRecord->normal);

  // enters material
  float n1 = 1;
  float n2 = refractionIndex;

  // leaves material
  if (hitRecord->normal->dot(*hitRecord->wIn) <= 0) {
    n1 = refractionIndex;
    n2 = 1;
    normal.negate();
  }

  float cosThetaI = -wIn.dot(normal);
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
    : refractionIndex(refractionIndex), ks(1) {}

RefractiveMaterial::RefractiveMaterial(float refractionIndex, Spectrum* ks)
    : refractionIndex(refractionIndex), ks(*ks) {}

Spectrum* RefractiveMaterial::evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut,
                                           Vector3f* wIn) const {
  return new Spectrum();
}

Spectrum* RefractiveMaterial::evaluateEmission(HitRecord*, Vector3f*) const {
  return new Spectrum();
}

bool RefractiveMaterial::hasSpecularReflection() const { return true; }

bool RefractiveMaterial::hasSpecularRefraction() const { return true; }

bool RefractiveMaterial::castsShadows() const { return false; }

ShadingSample RefractiveMaterial::evaluateSpecularReflection(HitRecord* hitRecord) const {
  auto reflectedDir = hitRecord->wIn->invReflected(*hitRecord->normal);
  float r = fresnelFactor(hitRecord);

  Spectrum brdf = Spectrum(r);
  return ShadingSample(brdf, Spectrum(0), *reflectedDir, true, r);
}

ShadingSample RefractiveMaterial::evaluateSpecularRefraction(HitRecord* hitRecord) const {
  Vector3f wIn(*hitRecord->wIn);
  wIn.negate();
  wIn.normalize();

  Vector3f normal(*hitRecord->normal);

  // enters material
  float n1 = 1.0;
  float n2 = refractionIndex;

  // leaves material
  if (hitRecord->normal->dot(*hitRecord->wIn) <= 0.0) {
    n1 = refractionIndex;
    n2 = 1.0;
    normal.negate();
  }

  float cosThetaI = -wIn.dot(normal);
  float phaseVelocity = n1 / n2;
  float sin2ThetaT = pow(phaseVelocity, 2.0) * (1.0 - pow(cosThetaI, 2.0));
  if (sin2ThetaT > 1.0) {
    return ShadingSample();
  }

  Vector3f refractedDir = wIn;
  refractedDir.scale(phaseVelocity);

  Vector3f scaledNormal(normal);
  scaledNormal.scale(phaseVelocity * cosThetaI - sqrt(1.0 - sin2ThetaT));
  refractedDir.add(scaledNormal);

  Spectrum brdf = Spectrum(ks);
  float r = fresnelFactor(hitRecord);
  brdf.scale(1.0 - r);

  return ShadingSample(brdf, Spectrum(0), refractedDir, true, r);
}
