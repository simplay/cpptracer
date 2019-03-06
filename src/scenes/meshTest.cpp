#include "meshTest.h"
#include "../intersectables/plane.h"
#include "../intersectables/sphere.h"
#include "../intersectables/mesh.h"
#include "../intersectables/instance.h"
#include "../materials/blinn.h"
#include "../materials/diffuse.h"
#include "../materials/gridTexturedMaterial.h"
#include "../integrators/debugIntegrator.h"
#include "../integrators/whittedIntegrator.h"
#include "../samplers/randomSampler.h"

MeshTest::MeshTest(int width, int height)
  : Scene(width, height) {}

  void MeshTest::buildCamera() {
    Vector3f* eye = new Vector3f(1.0, 4.0, 6.0);
    Vector3f* lookAt = new Vector3f(0.0, 0.0, 0.0);
    Vector3f* up = new Vector3f(0.0, 1.0, 0.0);
    float fov = 60.0;

    float aspectRatio = (float)width / height;

    Camera* camera = new Camera(
      eye, lookAt, up, fov, aspectRatio, width, height
    );
    this->camera = camera;
  }

void MeshTest::buildLights() {
  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(new Vector3f(0.5, 1.5, 2), new Spectrum(10.0)));
  lightList->push_back(new PointLight(new Vector3f(-0.75, 0.75, 2.0), new Spectrum(7.0)));
  this->lightList = lightList;
}

void MeshTest::buildIntersectables() {
  IntersectableList* intersectableList = new IntersectableList();
  Blinn* material = new Blinn(new Spectrum(0.5, 0.5, 0.0), new Spectrum(0.6), 50.0);

  GridTexturedMaterial* grid = new GridTexturedMaterial(
    new Spectrum(0.2f, 0.f, 0.f),
    new Spectrum(1.f, 1.f, 1.f),
    0.01f,
    new Vector3f(0.f, 0.f, 0.f),
    0.125f
  );

  Matrix4f* transform = new Matrix4f(
    1, 0, 0, 1,
    0, 0, -1, -1,
    0, 1, 0, 0,
    0, 0, 0, 1
  );

  Mesh* mesh = new Mesh(material, "../meshes/teapot.obj");
  Instance* instance = new Instance(mesh, transform);
  intersectableList->put(instance);
  intersectableList->put(new Plane(grid, Vector3f(0.0, 0.0, 1.0f), 2.15));
  this->intersectableList = intersectableList;
}

void MeshTest::buildIntegrator() {
  this->integrator = new WhittedIntegrator(this);
}

void MeshTest::buildSampler() {
  this->sampler = new RandomSampler();
}
