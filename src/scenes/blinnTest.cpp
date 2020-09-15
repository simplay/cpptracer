#include "scenes/blinnTest.h"
#include "integrators/whittedIntegrator.h"
#include "intersectables/geometries/plane.h"
#include "intersectables/geometries/sphere.h"
#include "materials/blinn.h"
#include "materials/diffuse.h"

BlinnTest::BlinnTest(int width, int height) : Scene(width, height) {}

void BlinnTest::buildCamera() {
  Vector3f* eye = new Vector3f(0.0, 0.0, 3.0);
  Vector3f* lookAt = new Vector3f(0.0, 0.0, 0.0);
  Vector3f* up = new Vector3f(0.0, 1.0, 0.0);
  float fov = 60.0;

  float aspectRatio = (float)width / height;

  Camera* camera = new Camera(eye, lookAt, up, fov, aspectRatio, width, height);
  this->camera = camera;
}

void BlinnTest::buildLights() {
  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(Vector3f(0.5, 0.5, 2.0), new Spectrum(1.0)));
  lightList->push_back(new PointLight(Vector3f(-0.75, 0.75, 2.0), new Spectrum(1.0, 0.0, 10.0)));
  this->lightList = lightList;
}

void BlinnTest::buildIntersectables() {
  IntersectableList* intersectableList = new IntersectableList();
  Blinn* material = new Blinn(new Spectrum(0.5, 0.5, 0.0), new Spectrum(0.6), 50.0);
  Material* diffuse = new Diffuse(new Spectrum(0.0, 0.5, 0.5));
  intersectableList->put(new Sphere(material, Vector3f(0.0, 0.0, 0.0), 0.5));
  intersectableList->put(new Plane(diffuse, Vector3f(1.0, 0.0, 0.0), 1));
  intersectableList->put(new Plane(diffuse, Vector3f(-1.0, 0.0, 0.0), 1));
  intersectableList->put(new Plane(diffuse, Vector3f(0.0, 1.0, 0.0), 1));
  intersectableList->put(new Plane(diffuse, Vector3f(0.0, -1.0, 0.0), 1));
  intersectableList->put(new Plane(diffuse, Vector3f(0.0, 0.0, 1.0), 1));
  this->intersectableList = intersectableList;
}

void BlinnTest::buildIntegrator() {
  // this->integrator = new DebugIntegrator(this);
  this->integrator = new WhittedIntegrator(this->intersectableList, this->lightList);
}
