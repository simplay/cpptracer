#include "meshTest.h"
#include "../intersectables/plane.h"
#include "../intersectables/sphere.h"
#include "../intersectables/mesh.h"
#include "../materials/blinn.h"
#include "../materials/diffuse.h"
#include "../materials/gridTexturedMaterial.h"
#include "../integrators/debugIntegrator.h"
#include "../integrators/pointLightIntegrator.h"
#include "../integrators/whittedIntegrator.h"

MeshTest::MeshTest(int width, int height)
  : Scene(width, height) {}

  void MeshTest::buildCamera() {
    Point3f* eye = new Point3f(0.0, 0.0, 5.0);
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
  IntersectableList* intersectableList = new IntersectableList();
  Material* material = new Diffuse(new Spectrum(1.0));
  GridTexturedMaterial* grid = new GridTexturedMaterial(
      new Spectrum(0.2f, 0.f, 0.f),
      new Spectrum(1.f, 1.f, 1.f),
      0.01f,
      new Point3f(0.f, 0.f, 0.f),
      0.125f
      );
  Mesh* mesh = new Mesh(material);
  intersectableList->put(mesh);
  intersectableList->put(new Plane(grid, new Point3f(0.0, 0.0, 1.0f), 2.15));
  this->intersectableList = intersectableList;
}

void MeshTest::buildIntegrator() {
  // this->integrator = new DebugIntegrator(this);
  this->integrator = new WhittedIntegrator(this);
}

