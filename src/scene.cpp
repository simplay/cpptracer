#include <vector>
#include "scene.h"
#include "plane.h"
#include "diffuse.h"
#include "pointLightIntegrator.h"
#include <iostream>

Scene::Scene(int width, int height) {
  // build camera matrix
  Point3f* eye = new Point3f(0.5, 0.5, 3.0);
  Point3f* lookAt = new Point3f(0.5, 0.0, 0.0);
  Point3f* up = new Point3f(0.2, 1.0, 0.0);
  float fov = 60.0;

  float aspectRatio = (float)width / height;

  Camera* camera = new Camera(
      eye, lookAt, up, fov, aspectRatio, width, height
  );

  Film* film = new Film(width, height);

  Material* material = new Diffuse(new Spectrum(1.0));
  IntersectableList* intersectableList = new IntersectableList();
  intersectableList->put(new Plane(material, new Point3f(1.0, 0.0, 0.0), 1));
  intersectableList->put(new Plane(material, new Point3f(-1.0, 0.0, 0.0), 1));
  intersectableList->put(new Plane(material, new Point3f(0.0, 1.0, 0.0), 1));
  intersectableList->put(new Plane(material, new Point3f(0.0, -1.0, 0.0), 1));
  intersectableList->put(new Plane(material, new Point3f(0.0, 0.0, 1.0), 1));

  std::vector<PointLight*>* lightList = new std::vector<PointLight*>;
  lightList->push_back(new PointLight(new Point3f(0.0, 0.0, 3.0), new Spectrum(10.0)));

  this->film = film;
  this->camera = camera;
  this->lightList = lightList;
  this->intersectableList = intersectableList;
  this->integrator = new PointLightIntegrator(this);
}
