#include "exampleConfig.h"
#include <iostream>
#include <thread>
#include "renderer.h"
#include "cameraTest.h"
#include "blinnTest.h"
#include "explosionTest.h"
#include "triangleTest.h"
#include "reflectionTest.h"
#include "refractiveScene.h"
#include "meshTest.h"
#include "cxxopts.hpp"

using namespace std;

cxxopts::ParseResult parse(int argc, char* argv[]) {
  // clang-format off
  try {
    cxxopts::Options options(argv[0], "For example: ./main.x -w 200 -h 200 -s 2 -i 6");

    options
      .allow_unrecognised_options()
      .add_options()
      ("w, width", "Image pixel width", cxxopts::value<int>()->default_value("100"))
      ("h, height", "Image pixel height", cxxopts::value<int>()->default_value("100"))
      ("s, spp", "Samples per pixel", cxxopts::value<int>()->default_value("1"))
      ("i, input-scene", "The scene to render", cxxopts::value<int>()->default_value("1"))
      ("help", "Print this help message")
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
      std::cout << options.help({""}) << std::endl;
      exit(0);
    }

    return result;

  } catch (const cxxopts::OptionException& e) {
    std::cout << "Error parsing options: " << e.what() << std::endl;
    exit(1);
  }
  // clang-format off
}

int main(int argc, char *argv[]) {
    cout << "C++ Raytracer v"
         << PROJECT_VERSION_MAJOR
         << "."
         << PROJECT_VERSION_MINOR
         << endl;

    auto result = parse(argc, argv);

    // // Default image resolution that should be used in case there were no args
    // // provided
    int width = result["w"].as<int>();
    int height = result["h"].as<int>();
    int sceneNr = result["i"].as<int>();
    int spp = result["s"].as<int>();

    unsigned threadCount = thread::hardware_concurrency();
    cout << "Using " << threadCount << " threads" << endl;
    cout << "Rendering scene Nr " << sceneNr << endl;
    cout << "Rendering " << spp << " sample(s) per pixel" << endl;

    Scene* scene;
    switch(sceneNr) {
      case 1:
        scene = new CameraTest(width, height);
        break;
      case 2:
        scene = new BlinnTest(width, height);
        break;
      case 3:
        scene = new ExplosionTest(width, height);
        break;
      case 4:
        scene = new TriangleTest(width, height);
        break;
      case 5:
        scene = new ReflectionTest(width, height);
        break;
      case 6:
        scene = new RefractiveTest(width, height);
        break;
      case 7:
        scene = new MeshTest(width, height);
        break;
      default:
        scene = new CameraTest(width, height);
    };
    scene->setup();

    Renderer renderer(scene);
    renderer.render(threadCount, spp);

    return 0;
}
