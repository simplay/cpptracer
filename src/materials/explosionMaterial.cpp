#include <math.h>
#include "explosionMaterial.h"

ExplosionMaterial::ExplosionMaterial(Spectrum* diffuseContribution, Spectrum* specularContribution, float shinynessPower)
  : diffuseContribution(diffuseContribution), specularContribution(specularContribution), shinynessPower(shinynessPower){
  }

Spectrum* ExplosionMaterial::evaluateBrdf(HitRecord* hitRecord, Point3f* wOut, Point3f* wIn) {
  Spectrum* contribution = new Spectrum();
  Spectrum* diffuse  = new Spectrum();
  Spectrum* specular = new Spectrum(specularContribution);
  Spectrum* ambient  = new Spectrum(diffuseContribution);

  Point3f* halfwayVector = new Point3f(wIn);
  halfwayVector->add(wOut);
  halfwayVector->normalize();

  specular->scale(pow(halfwayVector->dot(hitRecord->normal), shinynessPower));

  float d = hitRecord->t;
  Spectrum   yellow(1.7, 1.3, 1.0);
  Spectrum   orange(1.0, 0.6, 0.0);
  Spectrum      red(1.0, 0.0, 0.0);
  Spectrum darkgray(0.2, 0.2, 0.2);
  Spectrum     gray(0.4, 0.4, 0.4);

  float x = std::max(0.f, std::min(1.f, d));
  if (x < 0.25f) {
    diffuse = lerp(&gray, &darkgray, x * 4.f);
  } else if (x < 0.5f) {
    diffuse = lerp(&darkgray, &red, x * 4.f - 1.f);
  } else if (x < 0.75f) {
    diffuse = lerp(&red, &orange, x * 4.f - 2.f);
  } else {
    diffuse = lerp(&orange, &yellow, x * 4.f - 3.f);
  }
  diffuse->scale(wIn->dot(hitRecord->normal));

  contribution->add(diffuse);
  contribution->add(specular);
  contribution->add(ambient);

  return contribution;
}

Spectrum* ExplosionMaterial::evaluateEmission(HitRecord*, Point3f*) {
  return new Spectrum();
}

bool ExplosionMaterial::hasSpecularReflection() {
  return false;
}

bool ExplosionMaterial::hasSpecularRefraction() {
  return false;
}

bool ExplosionMaterial::castsShadows() {
  return true;
}

