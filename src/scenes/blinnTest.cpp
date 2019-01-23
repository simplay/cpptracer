#include "blinnTest.h"
#include "../intersectables/plane.h"
#include "../materials/blinn.h"

BlinnTest::BlinnTest(int width, int height)
  : Scene(width, height) {}

void BlinnTest::buildLights() {
  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(new Point3f(0.5, 0.5, 2.0), new Spectrum(1.0)));
  lightList->push_back(new PointLight(new Point3f(-0.75, 0.75, 2.0), new Spectrum(1.0, 0.0, 10.0)));
  this->lightList = lightList;
}

void BlinnTest::buildIntersectables() {
  IntersectableList* intersectableList = new IntersectableList();
  Blinn* material = new Blinn(new Spectrum(1.0, 0.0, 0.0), new Spectrum(0.6), 50.0);
  intersectableList->put(new Plane(material, new Point3f(1.0, 0.0, 0.0), 1));
  intersectableList->put(new Plane(material, new Point3f(-1.0, 0.0, 0.0), 1));
  intersectableList->put(new Plane(material, new Point3f(0.0, 1.0, 0.0), 1));
  intersectableList->put(new Plane(material, new Point3f(0.0, -1.0, 0.0), 1));
  intersectableList->put(new Plane(material, new Point3f(0.0, 0.0, 1.0), 1));
  this->intersectableList = intersectableList;
}
