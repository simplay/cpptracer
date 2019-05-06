#include "scenes/triangleTest.h"
#include "integrators/debugIntegrator.h"
#include "intersectables/containers/instance.h"
#include "intersectables/geometries/meshTriangle.h"
#include "intersectables/geometries/triangle.h"
#include "materials/diffuse.h"
#include "math/matrix4f.h"

TriangleTest::TriangleTest(int width, int height) : Scene(width, height) {}

void TriangleTest::buildLights() {
  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(Vector3f(0.0, 0.0, 3.0), new Spectrum(10.0)));
  this->lightList = lightList;
}

void TriangleTest::buildIntersectables() {
  Material* material = new Diffuse(new Spectrum(1.0));
  IntersectableList* intersectableList = new IntersectableList();
  auto tri = new Triangle(1, material, Vector3f(0.0, 0.0, 0.0), Vector3f(1.0, 0.0, 0.0),
                          Vector3f(0.0, 1.0, 0.0));

  // clang-format off
  Matrix4f* transform = new Matrix4f(
    1.0, 0.0, 0.0, 1.2,
    0.0, 0.8, 0.0, -1.2,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
  );
  // clang-format on

  auto instance = new Instance(tri);
  auto transformedInstance = new Instance(tri, transform);

  intersectableList->put(instance);
  intersectableList->put(transformedInstance);
  this->intersectableList = intersectableList;
}

void TriangleTest::buildIntegrator() { this->integrator = new DebugIntegrator(this); }
