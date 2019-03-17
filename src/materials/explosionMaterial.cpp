#include "materials/explosionMaterial.h"
#include <math.h>

// TODO(panmari): Change constructor to only allow const ref. Currently, this is a memory leak.
ExplosionMaterial::ExplosionMaterial(Spectrum* diffuseContribution, Spectrum* specularContribution,
                                     float shinynessPower)
    : diffuseContribution(*diffuseContribution),
      specularContribution(*specularContribution),
      shinynessPower(shinynessPower) {}

Spectrum* ExplosionMaterial::evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn) {
  Spectrum diffuse = Spectrum();
  Spectrum specular = specularContribution;
  Spectrum ambient = diffuseContribution;

  Vector3f halfwayVector = *wIn;
  halfwayVector.add(*wOut);
  halfwayVector.normalize();

  specular.scale(pow(halfwayVector.dot(*hitRecord->normal), shinynessPower));

  float d = hitRecord->t;
  const Spectrum yellow(1.7, 1.3, 1.0);
  const Spectrum orange(1.0, 0.6, 0.0);
  const Spectrum red(1.0, 0.0, 0.0);
  const Spectrum darkgray(0.2, 0.2, 0.2);
  const Spectrum gray(0.4, 0.4, 0.4);

  float x = std::max(0.f, std::min(1.f, d));
  if (x < 0.25f) {
    diffuse = lerp(gray, darkgray, x * 4.f);
  } else if (x < 0.5f) {
    diffuse = lerp(darkgray, red, x * 4.f - 1.f);
  } else if (x < 0.75f) {
    diffuse = lerp(red, orange, x * 4.f - 2.f);
  } else {
    diffuse = lerp(orange, yellow, x * 4.f - 3.f);
  }
  diffuse.scale(wIn->dot(*hitRecord->normal));

  Spectrum* contribution = new Spectrum();
  contribution->add(diffuse);
  contribution->add(specular);
  contribution->add(ambient);

  return contribution;
}

Spectrum* ExplosionMaterial::evaluateEmission(HitRecord*, Vector3f*) { return new Spectrum(); }

bool ExplosionMaterial::hasSpecularReflection() { return false; }

bool ExplosionMaterial::hasSpecularRefraction() { return false; }

bool ExplosionMaterial::castsShadows() { return true; }

ShadingSample ExplosionMaterial::evaluateSpecularReflection(HitRecord*) const {
  return ShadingSample();
}

ShadingSample ExplosionMaterial::evaluateSpecularRefraction(HitRecord*) const {
  return ShadingSample();
}
