#include <vector>
#include <iostream>
#include <iostream>
#include "scenes/scene.h"
#include "integrators/whittedIntegrator.h"
#include "samplers/oneSampler.h"

Scene::Scene(int width, int height): width(width), height(height) {}

// TODO how to call this in the constructor
void Scene::setup() {
  buildFilm();
  buildCamera();
  buildIntersectables();
  buildLights();
  buildIntegrator();
  buildSampler();
}

std::string Scene::filename() {
  return "image.bmp";
}

void Scene::buildFilm() {
  Film* film = new Film(width, height);
  this->film = film;
}

void Scene::buildCamera() {
  Vector3f* eye = new Vector3f(0.5, 0.5, 3.0);
  Vector3f* lookAt = new Vector3f(0.5, 0.0, 0.0);
  Vector3f* up = new Vector3f(0.0, 1.0, 0.0);
  float fov = 60.0;

  float aspectRatio = (float)width / height;

  Camera* camera = new Camera(
    eye, lookAt, up, fov, aspectRatio, width, height
  );
  this->camera = camera;
}

void Scene::buildLights() {
  std::cout << "Scene#buildLights not implemented yet." << std::endl;
}

void Scene::buildIntersectables() {
  std::cout << "Scene#buildIntersectables not implemented yet." << std::endl;
}

void Scene::buildIntegrator() {
  this->integrator = new WhittedIntegrator(this);
}

void Scene::buildSampler() {
  this->sampler = new OneSampler();
}
