#include "meshTest.h"
#include "../intersectables/plane.h"
#include "../intersectables/sphere.h"
#include "../intersectables/mesh.h"
#include "../materials/blinn.h"
#include "../materials/diffuse.h"
#include "../integrators/debugIntegrator.h"
#include "../integrators/pointLightIntegrator.h"
#include "../integrators/whittedIntegrator.h"

MeshTest::MeshTest(int width, int height)
  : Scene(width, height) {}

  void MeshTest::buildCamera() {
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

void MeshTest::buildLights() {
  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(new Point3f(0.5, 1.5, 2), new Spectrum(10.0)));
  lightList->push_back(new PointLight(new Point3f(-0.75, 0.75, 2.0), new Spectrum(7.0)));
  this->lightList = lightList;
}

void MeshTest::buildIntersectables() {
  Material* material = new Diffuse(new Spectrum(1.0));
  Mesh* mesh = new Mesh(material);
  this->intersectableList = mesh;
}

void MeshTest::buildIntegrator() {
  this->integrator = new DebugIntegrator(this);
  // this->integrator = new WhittedIntegrator(this);
}

