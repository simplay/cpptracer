
#include "cubeTest.h"
#include "../intersectables/rectangle.h"
#include "../materials/blinn.h"
#include "../materials/diffuse.h"
#include "../integrators/debugIntegrator.h"
#include "../integrators/whittedIntegrator.h"

CubeTest::CubeTest(int width, int height)
  : Scene(width, height) {}

void CubeTest::buildCamera() {
  Point3f* eye = new Point3f(0.0, 0.0, 3.0);
  Point3f* lookAt = new Point3f(0.0, 0.0, 0.0);
  Point3f* up = new Point3f(0.0, 1.0, 0.0);
  float fov = 60.0;

  float aspectRatio = (float)width / height;

  Camera* camera = new Camera(
    eye, lookAt, up, fov, aspectRatio, width, height
  );
  this->camera = camera;
}

void CubeTest::buildLights() {
  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(new Point3f(0.5, 0.5, 2.0), new Spectrum(1.0)));
  lightList->push_back(new PointLight(new Point3f(-0.75, 0.75, 2.0), new Spectrum(1.0, 0.0, 10.0)));
  this->lightList = lightList;
}

void CubeTest::buildIntersectables() {
  IntersectableList* intersectableList = new IntersectableList();
  Blinn* material = new Blinn(new Spectrum(0.5, 0.5, 0.0), new Spectrum(0.6), 50.0);
  Material* diffuse = new Diffuse(new Spectrum(0.0, 0.5, 0.5));
  intersectableList->put(new Rectangle(diffuse, new Point3f(0.0, 0.0, 1.0), 1));
  this->intersectableList = intersectableList;
}

void CubeTest::buildIntegrator() {
  // this->integrator = new DebugIntegrator(this);
  this->integrator = new WhittedIntegrator(this);
}
