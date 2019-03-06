#include "refractiveScene.h"
#include "../intersectables/plane.h"
#include "../intersectables/sphere.h"
#include "../materials/reflectiveMaterial.h"
#include "../materials/diffuse.h"
#include "../materials/blinn.h"
#include "../materials/refractiveMaterial.h"
#include "../materials/gridTexturedMaterial.h"
#include "../integrators/whittedIntegrator.h"
#include "../integrators/debugIntegrator.h"
#include "../samplers/randomSampler.h"

RefractiveTest::RefractiveTest(int width, int height)
  : Scene(width, height) {}


void RefractiveTest::buildCamera() {
  Vector3f* eye = new Vector3f(0.0, 0.0, 3.0);
  Vector3f* lookAt = new Vector3f(0.0, 0.0, 0.0);
  Vector3f* up = new Vector3f(0.0, 1.0, 0.0);
  float fov = 60.0;

  float aspectRatio = (float)width / height;

  Camera* camera = new Camera(
    eye, lookAt, up, fov, aspectRatio, width, height
  );
  this->camera = camera;
}

void RefractiveTest::buildLights() {
  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  Vector3f* lightPos = new Vector3f(0.0, 0.0, 3.0);
  lightPos->add(new Vector3f(-1.f, 0.f, 0.f));
  lightList->push_back(new PointLight(lightPos, new Spectrum(14.f, 14.f, 14.f)));
  lightPos->add(new Vector3f(2.f, 0.f, 0.f));
  lightList->push_back(new PointLight(lightPos, new Spectrum(14.f, 14.f, 14.f)));
  lightList->push_back(new PointLight(new Vector3f(0.7f, 0.7f, 0.7f), new Spectrum(14.f, 14.f, 14.f)));
  this->lightList = lightList;
}

void RefractiveTest::buildIntersectables() {
  IntersectableList* intersectableList = new IntersectableList();

  RefractiveMaterial* material = new RefractiveMaterial(1.1);
  GridTexturedMaterial* grid = new GridTexturedMaterial(
    new Spectrum(0.2f, 0.f, 0.f),
    new Spectrum(1.f, 1.f, 1.f),
    0.01f,
    new Vector3f(0.f, 0.f, 0.f),
    0.125f
  );

  intersectableList->put(new Sphere(material, new Vector3f(0.0, 0.0, 0.0), 1.0));
  intersectableList->put(new Plane(grid, Vector3f(0.0, 0.0, 1.0f), 2.15));

  this->intersectableList = intersectableList;
}

void RefractiveTest::buildIntegrator() {
  // this->integrator = new DebugIntegrator(this);
  this->integrator = new WhittedIntegrator(this);
}

void RefractiveTest::buildSampler() {
  this->sampler = new RandomSampler();
}
