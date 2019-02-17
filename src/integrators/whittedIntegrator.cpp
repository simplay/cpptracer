#include <iostream>
#include <algorithm>
#include "whittedIntegrator.h"
#include "../materials/material.h"

bool WhittedIntegrator::isOccluded(Point3f* hitPosition, Point3f* lightDir, float eps) {
  Ray shadowRay(
    new Point3f(hitPosition),
    lightDir
  );

  HitRecord* shadowHit = scene->intersectableList->intersect(&shadowRay);
  if (!shadowHit->isValid()) {
    delete shadowRay.origin;
    delete shadowHit;
    return false;
  }

  Point3f dist_shad_hit_view_hit2(shadowHit->position);
  dist_shad_hit_view_hit2.sub(hitPosition);
  bool hasShadowHit = shadowHit->material->castsShadows() && (dist_shad_hit_view_hit2.dot() < eps);
  delete shadowHit;
  delete shadowRay.origin;

  return hasShadowHit;
}

Spectrum* WhittedIntegrator::contributionOf(PointLight* lightSource, HitRecord* hitRecord) {
  HitRecord* lightHit = lightSource->sample();
  Point3f lightDir(lightHit->position);
  lightDir.sub(hitRecord->position);

  float d2 = lightDir.dot();
  lightDir.normalize();

  if (isOccluded(hitRecord->position, &lightDir, d2)) {
    delete lightHit;
    return new Spectrum();
  }

  Spectrum* brdfContribution = hitRecord->material->evaluateBrdf(hitRecord, hitRecord->wIn, &lightDir);

  // shading: brdf * emission * dot(normal,light_dir) * geom_term
  Spectrum* contribution = new Spectrum(brdfContribution);
  delete brdfContribution;

  Point3f oppositeLightDir(lightDir);
  oppositeLightDir.negate();

  Spectrum lightEmission(lightHit->material->evaluateEmission(lightHit, &oppositeLightDir));
  delete lightHit;

  contribution->mult(&lightEmission);

  float angle = hitRecord->normal->dot(&lightDir);
  float cosTheta = 0 > angle ? 0 : angle;
  contribution->scale(cosTheta);

  // find a better scaling approach
  contribution->scale(1.0 / d2);

  return contribution;
}

WhittedIntegrator::WhittedIntegrator(Scene* scene): scene(scene) {}

Spectrum* WhittedIntegrator::integrate(Ray* ray) {
  int MAX_DEPTH = 5;

  HitRecord* hitRecord = scene->intersectableList->intersect(ray);
  if (!hitRecord->isValid()) {
    // only delete hitRecord for deepest hit record
    if (ray->depth == MAX_DEPTH) {
      delete hitRecord;
    }
    return new Spectrum();
  }

  Spectrum reflection;
  Spectrum refraction;

  if (hitRecord->material->hasSpecularReflection() && ray->depth < MAX_DEPTH) {
    ShadingSample* sample = hitRecord->material->evaluateSpecularReflection(hitRecord);
    if (sample->isValid) {
      reflection.add(sample->brdf);
      Ray reflectedRay(new Point3f(hitRecord->position), sample->w, ray->depth + 1);
      Spectrum* spec = integrate(&reflectedRay);
      reflection.mult(spec);
      delete reflectedRay.origin;
      delete spec;
    }
    delete sample;
  }

  if (hitRecord->material->hasSpecularRefraction() && ray->depth < MAX_DEPTH) {
    ShadingSample* sample = hitRecord->material->evaluateSpecularRefraction(hitRecord);
    if (sample->isValid) {
      refraction.add(sample->brdf);

      Ray refractedRay(new Point3f(hitRecord->position), sample->w, ray->depth + 1);
      Spectrum* spec = integrate(&refractedRay);
      refraction.mult(spec);

      delete refractedRay.origin;
      delete sample;
      delete spec;
    }
  }

  if (hitRecord->material->hasSpecularReflection() || hitRecord->material->hasSpecularRefraction()) {
    Spectrum* total = new Spectrum();
    total->add(&reflection);
    total->add(&refraction);

    return total;
  }

  Spectrum* contribution = new Spectrum();
  for (auto const& lightSource: *scene->lightList) {
    Spectrum* currentContribution = contributionOf(lightSource, hitRecord);
    contribution->add(currentContribution);
    delete currentContribution;
  }
  delete hitRecord;

  return contribution;
}

