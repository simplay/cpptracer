#include "triangleTest.h"
#include "../intersectables/triangle.h"
#include "../intersectables/meshTriangle.h"
#include "../intersectables/instance.h"
#include "../materials/diffuse.h"
#include "../integrators/debugIntegrator.h"
#include "../math/matrix4f.h"

TriangleTest::TriangleTest(int width, int height)
  : Scene(width, height) {}

void TriangleTest::buildLights() {
  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(new Point3f(0.0, 0.0, 3.0), new Spectrum(10.0)));
  this->lightList = lightList;
}

void TriangleTest::buildIntersectables() {
  Material* material = new Diffuse(new Spectrum(1.0));
  IntersectableList* intersectableList = new IntersectableList();
  auto tri = new Triangle(
    1,
    material,
    new Point3f(0.0, 0.0, 0.0),
    new Point3f(1.0, 0.0, 0.0),
    new Point3f(0.0, 1.0, 0.0)
  );

  Matrix4f* mat = new Matrix4f(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  );

  auto instance = new Instance(tri, mat);

  intersectableList->put(
      instance
  );
  this->intersectableList = intersectableList;
}

void TriangleTest::buildIntegrator() {
  this->integrator = new DebugIntegrator(this);
}
