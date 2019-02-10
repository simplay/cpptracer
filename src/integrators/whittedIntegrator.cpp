#include <iostream>
#include <algorithm>
#include "whittedIntegrator.h"
#include "../materials/material.h"

bool WhittedIntegrator::isOccluded(Point3f* hitPosition, Point3f* lightDir, float eps) {
  Ray* shadowRay = new Ray(
    hitPosition,
    lightDir
  );

  HitRecord* shadowHit = scene->intersectableList->intersect(shadowRay);
  if (!shadowHit->isValid()) {
    return false;
  }

  Point3f* dist_shad_hit_view_hit2 = (new Point3f(shadowHit->position));
  dist_shad_hit_view_hit2->sub(hitPosition);
  return shadowHit->material->castsShadows() && (dist_shad_hit_view_hit2->dot() < eps);
}

Spectrum* WhittedIntegrator::contributionOf(PointLight* lightSource, HitRecord* hitRecord) {
  HitRecord* lightHit = lightSource->sample();
  Point3f* lightDir = new Point3f(lightHit->position);
  lightDir->sub(hitRecord->position);

  float d2 = lightDir->dot();
  lightDir->normalize();

  if (isOccluded(hitRecord->position, lightDir, d2)) {
    return new Spectrum();
  }

  Spectrum* brdfContribution = hitRecord->material->evaluateBrdf(hitRecord, hitRecord->wIn, lightDir);

  // shading: brdf * emission * dot(normal,light_dir) * geom_term
  Spectrum* contribution = new Spectrum(brdfContribution);

  Point3f* oppositeLightDir = new Point3f(lightDir);
  oppositeLightDir->negate();

  Spectrum* lightEmission = lightHit->material->evaluateEmission(lightHit, oppositeLightDir);
  contribution->mult(lightEmission);

  float angle = hitRecord->normal->dot(lightDir);
  float cosTheta = 0 > angle ? 0 : angle;
  contribution->scale(cosTheta);

  // find a better scaling approach
  contribution->scale(1.0 / d2);
  return contribution;
}

WhittedIntegrator::WhittedIntegrator(Scene* scene): scene(scene) {}

Spectrum* WhittedIntegrator::integrate(Ray* ray) {
  HitRecord* hitRecord = scene->intersectableList->intersect(ray);
  if (!hitRecord->isValid()) {
    return new Spectrum();
  }
  int MAX_DEPTH = 5;

  Spectrum* reflection = new Spectrum();
  Spectrum* refraction = new Spectrum();

  if (hitRecord->material->hasSpecularReflection() && ray->depth < MAX_DEPTH) {
    ShadingSample* sample = hitRecord->material->evaluateSpecularReflection(hitRecord);
    if (sample->isValid) {
      reflection = new Spectrum(sample->brdf);

      Ray* reflectedRay = new Ray(hitRecord->position, sample->w, ray->depth + 1);
      Spectrum* spec = integrate(reflectedRay);
      reflection->mult(spec);
    }
  }

  if (hitRecord->material->hasSpecularRefraction() && ray->depth < MAX_DEPTH) {
    ShadingSample* sample = hitRecord->material->evaluateSpecularRefraction(hitRecord);
    if (sample->isValid) {
      refraction = new Spectrum(sample->brdf);

      Ray* refractedRay = new Ray(hitRecord->position, sample->w, ray->depth + 1);
      Spectrum* spec = integrate(refractedRay);
      refraction->mult(spec);
    }
  }

  if (hitRecord->material->hasSpecularReflection() || hitRecord->material->hasSpecularRefraction()) {
    Spectrum* total = new Spectrum();
    total->add(reflection);
    total->add(refraction);
    return total;
  }

  Spectrum* contribution = new Spectrum();
  for (auto const& lightSource: *scene->lightList) {
    Spectrum* currentContribution = contributionOf(lightSource, hitRecord);
    contribution->add(currentContribution);
  }

  return contribution;
}

