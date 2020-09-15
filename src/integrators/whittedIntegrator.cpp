#include "integrators/whittedIntegrator.h"
#include <algorithm>
#include <memory>
#include "materials/material.h"

bool WhittedIntegrator::isOccluded(Vector3f* hitPosition, Vector3f* lightDir, float eps) const {
  Ray shadowRay(new Vector3f(*hitPosition), lightDir);

  HitRecord* shadowHit = intersectableList->intersect(shadowRay);
  if (!shadowHit->isValid()) {
    delete shadowRay.origin;
    delete shadowHit;
    return false;
  }

  Vector3f dist_shad_hit_view_hit2(*shadowHit->position);
  dist_shad_hit_view_hit2.sub(*hitPosition);
  bool hasShadowHit = shadowHit->material->castsShadows() && (dist_shad_hit_view_hit2.dot() < eps);
  delete shadowHit;
  delete shadowRay.origin;

  return hasShadowHit;
}

Spectrum WhittedIntegrator::contributionOf(const PointLight* lightSource,
                                           HitRecord* hitRecord) const {
  HitRecord* lightHit = lightSource->sample();
  Vector3f lightDir(*lightHit->position);
  lightDir.sub(*hitRecord->position);

  float d2 = lightDir.dot();
  lightDir.normalize();

  if (isOccluded(hitRecord->position, &lightDir, d2)) {
    delete lightHit;
    return Spectrum(0);
  }

  Spectrum contribution = hitRecord->material->evaluateBrdf(hitRecord, hitRecord->wIn, &lightDir);

  // shading: brdf * emission * dot(normal,light_dir) * geom_term

  Vector3f oppositeLightDir(lightDir);
  oppositeLightDir.negate();

  Spectrum lightEmission = lightHit->material->evaluateEmission(lightHit, &oppositeLightDir);
  delete lightHit;

  contribution.mult(lightEmission);

  float angle = hitRecord->normal->dot(lightDir);
  float cosTheta = 0 > angle ? 0 : angle;
  contribution.scale(cosTheta);

  // find a better scaling approach
  contribution.scale(1.0 / d2);

  return contribution;
}

WhittedIntegrator::WhittedIntegrator(const IntersectableList* intersectableList,
                                     const std::vector<PointLight*>* lights)
    : intersectableList(intersectableList), lights(lights) {}

Spectrum WhittedIntegrator::integrate(const Ray& ray) const {
  constexpr int MAX_DEPTH = 5;

  auto hitRecord = std::unique_ptr<HitRecord>(intersectableList->intersect(ray));
  if (!hitRecord->isValid()) {
    return Spectrum();
  }

  Spectrum reflection;
  Spectrum refraction;

  if (hitRecord->material->hasSpecularReflection() && ray.depth < MAX_DEPTH) {
    ShadingSample sample = hitRecord->material->evaluateSpecularReflection(hitRecord.get());
    if (sample.isValid) {
      reflection.add(sample.brdf);
      Ray reflectedRay(new Vector3f(*hitRecord->position), new Vector3f(sample.w), ray.depth + 1);
      Spectrum spec = integrate(reflectedRay);
      reflection.mult(spec);
      delete reflectedRay.origin;
    }
  }

  if (hitRecord->material->hasSpecularRefraction() && ray.depth < MAX_DEPTH) {
    ShadingSample sample = hitRecord->material->evaluateSpecularRefraction(hitRecord.get());
    if (sample.isValid) {
      refraction.add(sample.brdf);

      const Ray refractedRay(new Vector3f(*hitRecord->position), new Vector3f(sample.w),
                             ray.depth + 1);
      Spectrum spec = integrate(refractedRay);
      refraction.mult(spec);

      delete refractedRay.origin;
    }
  }

  if (hitRecord->material->hasSpecularReflection() ||
      hitRecord->material->hasSpecularRefraction()) {
    Spectrum total = Spectrum(0);
    total.add(reflection);
    total.add(refraction);

    return total;
  }

  Spectrum contribution = Spectrum(0);
  for (const PointLight* lightSource : *lights) {
    Spectrum currentContribution = contributionOf(lightSource, hitRecord.get());
    contribution.add(currentContribution);
  }

  return contribution;
}
