#include <math.h>
#include "blinn.h"

Blinn::Blinn(Spectrum* diffuseContribution, Spectrum* specularContribution, float shinynessPower)
  : diffuseContribution(diffuseContribution), specularContribution(specularContribution), shinynessPower(shinynessPower){
}

Spectrum* Blinn::evaluateBrdf(HitRecord* hitRecord, Point3f* wOut, Point3f* wIn) {
  Spectrum* contribution = new Spectrum();
  Spectrum* diffuse  = new Spectrum(diffuseContribution);
  Spectrum* specular = new Spectrum(specularContribution);
  Spectrum* ambient  = new Spectrum(diffuseContribution);

  Point3f* halfwayVector = new Point3f(wIn);
  halfwayVector->add(wOut);
  halfwayVector->normalize();

  diffuse->scale(wIn->dot(hitRecord->normal));
  specular->scale(pow(halfwayVector->dot(hitRecord->normal), shinynessPower));

  contribution->add(diffuse);
  contribution->add(specular);
  contribution->add(ambient);

  return contribution;
}

Spectrum* Blinn::evaluateEmission(HitRecord*, Point3f*) {
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
