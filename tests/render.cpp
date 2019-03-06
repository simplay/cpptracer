#include <gtest/gtest.h>
#include "renderer.h"
#include "cameraTest.h"
#include "blinnTest.h"
#include "explosionTest.h"
#include "triangleTest.h"
#include "reflectionTest.h"
#include "refractiveScene.h"
#include "meshTest.h"

namespace {
  const int WIDTH = 40;
  const int HEIGHT = 40;
  const int SPP = 1;

TEST(Renderer, CameraTest) {
  auto scene = new CameraTest(WIDTH, HEIGHT);
  scene->setup();

  Renderer renderer(scene, false);
  renderer.render(1, SPP);
}

TEST(Renderer, BlinnTest) {
  auto scene = new BlinnTest(WIDTH, HEIGHT);
  scene->setup();

  Renderer renderer(scene, false);
  renderer.render(1, SPP);
}

TEST(Renderer, ExplosionTest) {
  auto scene = new ExplosionTest(WIDTH, HEIGHT);
  scene->setup();

  Renderer renderer(scene, false);
  renderer.render(1, SPP);
}

TEST(Renderer, ReflectionTest) {
  auto scene = new ReflectionTest(WIDTH, HEIGHT);
  scene->setup();

  Renderer renderer(scene, false);
  renderer.render(1, SPP);
}

TEST(Renderer, RefractiveTest) {
  auto scene = new RefractiveTest(WIDTH, HEIGHT);
  scene->setup();

  Renderer renderer(scene, false);
  renderer.render(1, SPP);
}

TEST(Renderer, MeshTest) {
  auto scene = new MeshTest(WIDTH, HEIGHT);
  scene->setup();

  Renderer renderer(scene, false);
  renderer.render(1, SPP);
}
}
