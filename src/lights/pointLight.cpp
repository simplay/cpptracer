#include "lights/pointLight.h"
#include "materials/material.h"
#include "materials/pointLightMaterial.h"

PointLight::PointLight(Vector3f position, Spectrum* emission)
    : position(position), material((Material*)new PointLightMaterial(emission)) {}

HitRecord* PointLight::sample() const { return new HitRecord(new Vector3f(position), material); }

HitRecord* PointLight::intersect(const Ray&) const { return new HitRecord(); }
