// usage:
//  ./main.x IMG_DIM
//  ./main.x IMG_WIDTH IMG_HEIGHT
//  ./main.x IMG_WIDTH IMG_HEIGHT SCENE_NR

#include "exampleConfig.h"
#include <iostream>
#include <thread>
#include <fstream>
#include "renderer.h"
#include "cameraTest.h"
#include "blinnTest.h"
#include "explosionTest.h"
#include "triangleTest.h"
#include "reflectionTest.h"
#include "refractiveScene.h"

using namespace std;

struct MeshData {
  string type;
  float x;
  float y;
  float z;
};

vector<MeshData> readInput(const char* filename) {
  vector<MeshData> mesh;
  ifstream file(filename);
  string line;
  while (getline(file, line)) {
    MeshData it;
    switch(line.c_str()[0]) {
      case 'v':
        sscanf(line.c_str(), "v %f %f %f", &it.x, &it.y, &it.z);
        it.type = "v";
        mesh.push_back(it);
        break;
      case 'f':
        sscanf(line.c_str(), "f %f %f %f", &it.x, &it.y, &it.z);
        it.type = "f";
        mesh.push_back(it);
        break;
      default:
        std::cout << "Unknown obj type: " << line << std::endl;
    }
  }
  return mesh;
}

int main(int argc, char *argv[]) {
    cout << "C++ Raytracer v"
         << PROJECT_VERSION_MAJOR
         << "."
         << PROJECT_VERSION_MINOR
         << endl;

    // Default image resolution that should be used in case there were no args
    // provided
    int width = 400;
    int height = 400;
    int sceneNr = 1;
    int spp = 1;

    if (argc == 2) {
      width = std::atoi(argv[1]);
      height = width;
    } else if (argc == 3) {
      width = std::atoi(argv[1]);
      height = std::atoi(argv[2]);
    } else if (argc == 4) {
      width = std::atoi(argv[1]);
      height = std::atoi(argv[2]);
      sceneNr = std::atoi(argv[3]);
    } else if (argc == 5) {
      width = std::atoi(argv[1]);
      height = std::atoi(argv[2]);
      sceneNr = std::atoi(argv[3]);
      spp = std::atoi(argv[4]);
    }

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
      default:
        scene = new CameraTest(width, height);
    };
    scene->setup();

    vector<MeshData> mesh = readInput("../meshes/teapot.obj");
    std::cout << "Nr. of lines extracted: " << mesh.size() << std::endl;

    Renderer renderer(scene);
    renderer.render(threadCount, spp);

    return 0;
}
