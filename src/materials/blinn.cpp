#include <math.h>
#include "materials/blinn.h"

Blinn::Blinn(Spectrum* diffuseContribution, Spectrum* specularContribution, float shinynessPower)
  : diffuseContribution(diffuseContribution), specularContribution(specularContribution), shinynessPower(shinynessPower){
}

Spectrum* Blinn::evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn) {
  Spectrum* contribution = new Spectrum();
  Spectrum* diffuse  = new Spectrum(diffuseContribution);
  Spectrum* specular = new Spectrum(specularContribution);
  Spectrum* ambient  = new Spectrum(diffuseContribution);

  Vector3f* halfwayVector = new Vector3f(wIn);
  halfwayVector->add(wOut);
  halfwayVector->normalize();

  diffuse->scale(wIn->dot(hitRecord->normal));
  specular->scale(pow(halfwayVector->dot(hitRecord->normal), shinynessPower));

  contribution->add(diffuse);
  contribution->add(specular);
  contribution->add(ambient);

  return contribution;
}

Spectrum* Blinn::evaluateEmission(HitRecord*, Vector3f*) {
  return new Spectrum();
}

bool Blinn::hasSpecularReflection() {
  return false;
}

bool Blinn::hasSpecularRefraction() {
  return false;
}

bool Blinn::castsShadows() {
  return true;
}

ShadingSample* Blinn::evaluateSpecularReflection(HitRecord* hitRecord) {
  return new ShadingSample();
}

ShadingSample* Blinn::evaluateSpecularRefraction(HitRecord* hitRecord) {
  return new ShadingSample();
}
