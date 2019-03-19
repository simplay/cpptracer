#include "materials/blinn.h"
#include <math.h>

// TODO(panmari): Change constructor to expect a const ref. This is currently a memory leak.
Blinn::Blinn(Spectrum* diffuseContribution, Spectrum* specularContribution, float shinynessPower)
    : diffuseContribution(*diffuseContribution),
      specularContribution(*specularContribution),
      shinynessPower(shinynessPower) {}

Spectrum* Blinn::evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn) const {
  Spectrum* contribution = new Spectrum();
  Spectrum diffuse = diffuseContribution;
  Spectrum specular = specularContribution;
  const Spectrum& ambient = diffuseContribution;

  Vector3f halfwayVector = *wIn;
  halfwayVector.add(*wOut);
  halfwayVector.normalize();

  diffuse.scale(wIn->dot(*hitRecord->normal));
  specular.scale(pow(halfwayVector.dot(*hitRecord->normal), shinynessPower));

  contribution->add(diffuse);
  contribution->add(specular);
  contribution->add(ambient);

  return contribution;
}

Spectrum* Blinn::evaluateEmission(HitRecord*, Vector3f*) const { return new Spectrum(); }

bool Blinn::hasSpecularReflection() const { return false; }

bool Blinn::hasSpecularRefraction() const { return false; }

bool Blinn::castsShadows() const { return true; }

ShadingSample Blinn::evaluateSpecularReflection(HitRecord*) const { return ShadingSample(); }

ShadingSample Blinn::evaluateSpecularRefraction(HitRecord*) const { return ShadingSample(); }
