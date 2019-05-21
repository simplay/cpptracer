#include "scenes/csgScene.h"
#include "integrators/debugIntegrator.h"
#include "integrators/whittedIntegrator.h"
#include "intersectables/csg/csgInstance.h"
#include "intersectables/csg/csgNode.h"
#include "intersectables/geometries/cube.h"
#include "intersectables/geometries/plane.h"
#include "intersectables/geometries/sphere.h"
#include "materials/blinn.h"
#include "materials/diffuse.h"

CsgScene::CsgScene(int width, int height) : Scene(width, height) {}

void CsgScene::buildCamera() {
  Vector3f* eye = new Vector3f(0.0, 0.0, 2.5);

  // positive x => bottom negative x => top
  // positive y => right  negative y => left
  Vector3f* lookAt = new Vector3f(0.0, 0.0, 0.0);

  Vector3f* up = new Vector3f(0.0, 1.0, 0.0);
  float fov = 60.0;

  float aspectRatio = (float)width / height;

  Camera* camera = new Camera(eye, lookAt, up, fov, aspectRatio, width, height);
  this->camera = camera;
}

void CsgScene::buildLights() {
  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(Vector3f(0.5, 0, 2.0), new Spectrum(2)));
  this->lightList = lightList;
}

void CsgScene::buildIntersectables() {
  IntersectableList* intersectableList = new IntersectableList();
  Blinn* material = new Blinn(new Spectrum(0.5, 0.5, 0.0), new Spectrum(0.6), 50.0);
  Material* diffuse = new Diffuse(new Spectrum(0.0, 0.5, 0.5));

  auto s1 = new Sphere(material, Vector3f(0.0, -0.4, 0.0), 0.5);
  auto s2 = new Sphere(material, Vector3f(0.0, 0.4, 0.0), 0.5);
  auto s3 = new Sphere(material, Vector3f(0.0, 0.0, 0.0), 0.25);

  auto n = new CsgNode(s1, s2, SetOperation::INTERSECTION);
  auto node = new CsgNode(s3, n, SetOperation::INTERSECTION);

  // clang-format off
  Matrix4f* transform = new Matrix4f(
    2.5, 0.0, 0.0, 0.0,
    0.0, 2.5, 0.0, 0.0,
    0.0, 0.0, 2.5, 0.5,
    0.0, 0.0, 0.0, 1.0
  );
  // clang-format on
  auto instance = new CsgInstance(node, transform);
  intersectableList->put(instance);

  intersectableList->put(new Plane(diffuse, Vector3f(1.0, 0.0, 0.0), 1));   // top
  intersectableList->put(new Plane(diffuse, Vector3f(-1.0, 0.0, 0.0), 1));  // bottom
  intersectableList->put(new Plane(diffuse, Vector3f(0.0, 1.0, 0.0), 1));   // left
  intersectableList->put(new Plane(diffuse, Vector3f(0.0, -1.0, 0.0), 1));  // right
  intersectableList->put(new Plane(diffuse, Vector3f(0.0, 0.0, 1.0), 1));   // back

  this->intersectableList = intersectableList;
}

void CsgScene::buildIntegrator() {
  // this->integrator = new DebugIntegrator(this);
  this->integrator = new WhittedIntegrator(this->intersectableList, this->lightList);
}

