#include "integrators/whittedIntegrator.h"
#include "intersectables/plane.h"
#include "intersectables/sphere.h"
#include "materials/blinn.h"
#include "materials/diffuse.h"
#include "materials/reflectiveMaterial.h"
#include "samplers/oneSampler.h"
#include "samplers/randomSampler.h"
#include "scenes/reflectionTest.h"

ReflectionTest::ReflectionTest(int width, int height) : Scene(width, height) {}

void ReflectionTest::buildLights() {
  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(Vector3f(0.5, 0.5, -0.0), new Spectrum(1.0)));
  lightList->push_back(new PointLight(Vector3f(-0.75, 0.75, 3.0), new Spectrum(1.0, 1.0, 10.0)));
  this->lightList = lightList;
}

void ReflectionTest::buildIntersectables() {
  IntersectableList* intersectableList = new IntersectableList();
  ReflectiveMaterial* mirror = new ReflectiveMaterial();

  Blinn* blinn = new Blinn(new Spectrum(1.0, 0.0, 0.0), new Spectrum(0.6), 50.0);
  Blinn* blinn2 = new Blinn(new Spectrum(0.0, 1.0, 0.0), new Spectrum(0.6), 50.0);
  Material* diffuse = new Diffuse(new Spectrum(0.0, 0.5, 0.5));
  intersectableList->put(new Sphere(blinn, Vector3f(0.0, -0.4, 0.0), 0.5));
  intersectableList->put(new Sphere(blinn2, Vector3f(0.8, 0.5, 0), 0.35));

  intersectableList->put(new Plane(diffuse, Vector3f(-1.0, 0.0, 0.0), 1));
  intersectableList->put(new Plane(mirror, Vector3f(0.0, 1.0, 0.0), 1));
  intersectableList->put(new Plane(mirror, Vector3f(0.0, -1.0, 0.0), 1));
  intersectableList->put(new Plane(diffuse, Vector3f(0.0, 0.0, 1.0), 1));
  this->intersectableList = intersectableList;
}

void ReflectionTest::buildIntegrator() {
  this->integrator = new WhittedIntegrator(this->intersectableList, this->lightList);
}

void ReflectionTest::buildSampler() {
  this->sampler = new RandomSampler();
  // this->sampler = new OneSampler();
}
