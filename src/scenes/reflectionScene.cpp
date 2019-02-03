#include "reflectionTest.h"
#include "../intersectables/plane.h"
#include "../intersectables/sphere.h"
#include "../materials/reflectiveMaterial.h"
#include "../materials/diffuse.h"
#include "../integrators/whittedIntegrator.h"

ReflectionTest::ReflectionTest(int width, int height)
  : Scene(width, height) {}

void ReflectionTest::buildLights() {
  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(new Point3f(0.5, 0.5, 2.0), new Spectrum(1.0)));
  lightList->push_back(new PointLight(new Point3f(-0.75, 0.75, 2.0), new Spectrum(1.0, 0.0, 10.0)));
  this->lightList = lightList;
}

void ReflectionTest::buildIntersectables() {
  IntersectableList* intersectableList = new IntersectableList();
  ReflectiveMaterial* material = new ReflectiveMaterial();
  Material* diffuse = new Diffuse(new Spectrum(0.0, 0.5, 0.5));
  intersectableList->put(new Sphere(material, new Point3f(0.0, 0.0, 0.0), 0.5));
  intersectableList->put(new Plane(diffuse, new Point3f(1.0, 0.0, 0.0), 1));
  intersectableList->put(new Plane(diffuse, new Point3f(-1.0, 0.0, 0.0), 1));
  intersectableList->put(new Plane(diffuse, new Point3f(0.0, 1.0, 0.0), 1));
  intersectableList->put(new Plane(diffuse, new Point3f(0.0, -1.0, 0.0), 1));
  intersectableList->put(new Plane(diffuse, new Point3f(0.0, 0.0, 1.0), 1));
  this->intersectableList = intersectableList;
}

void ReflectionTest::buildIntegrator() {
  this->integrator = new WhittedIntegrator(this);
}
