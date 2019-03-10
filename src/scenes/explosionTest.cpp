#include "scenes/explosionTest.h"
#include "intersectables/explosion.h"
#include "intersectables/plane.h"
#include "intersectables/sphere.h"
#include "materials/diffuse.h"
#include "materials/explosionMaterial.h"

ExplosionTest::ExplosionTest(int width, int height) : Scene(width, height) {}

void ExplosionTest::buildLights() {
  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(Vector3f(0.5, 0.5, 2.0), new Spectrum(1.0)));
  lightList->push_back(new PointLight(Vector3f(-0.75, 0.75, 2.0), new Spectrum(1.0, 0.0, 10.0)));
  this->lightList = lightList;
}

void ExplosionTest::buildIntersectables() {
  IntersectableList* intersectableList = new IntersectableList();
  ExplosionMaterial* material =
      new ExplosionMaterial(new Spectrum(1.0, 0.0, 0.0), new Spectrum(0.6), 50.0);
  Material* diffuse = new Diffuse(new Spectrum(0.0, 0.5, 0.5));
  intersectableList->put(new Explosion(material, new Vector3f(0.0, 0.0, 0.0), 1.0));
  intersectableList->put(new Plane(diffuse, Vector3f(1.0, 0.0, 0.0), 1));
  intersectableList->put(new Plane(diffuse, Vector3f(-1.0, 0.0, 0.0), 1));
  intersectableList->put(new Plane(diffuse, Vector3f(0.0, 1.0, 0.0), 1));
  intersectableList->put(new Plane(diffuse, Vector3f(0.0, -1.0, 0.0), 1));
  intersectableList->put(new Plane(diffuse, Vector3f(0.0, 0.0, 1.0), 1));
  this->intersectableList = intersectableList;
}
