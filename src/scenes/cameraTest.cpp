#include "cameraTest.h"
#include "plane.h"
#include "diffuse.h"

CameraTest::CameraTest(int width, int height)
  : Scene(width, height) {}

void CameraTest::buildLights() {
  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(new Point3f(0.0, 0.0, 3.0), new Spectrum(10.0)));
  this->lightList = lightList;
}

void CameraTest::buildIntersectables() {
  Material* material = new Diffuse(new Spectrum(1.0));
  IntersectableList* intersectableList = new IntersectableList();
  intersectableList->put(new Plane(material, new Point3f(1.0, 0.0, 0.0), 1));
  intersectableList->put(new Plane(material, new Point3f(-1.0, 0.0, 0.0), 1));
  intersectableList->put(new Plane(material, new Point3f(0.0, 1.0, 0.0), 1));
  intersectableList->put(new Plane(material, new Point3f(0.0, -1.0, 0.0), 1));
  intersectableList->put(new Plane(material, new Point3f(0.0, 0.0, 1.0), 1));
  this->intersectableList = intersectableList;
}
