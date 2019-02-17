// usage:
//  ./main.x IMG_DIM
//  ./main.x IMG_WIDTH IMG_HEIGHT
//  ./main.x IMG_WIDTH IMG_HEIGHT SCENE_NR

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


#include <fstream>


using namespace std;

struct MeshData {
  vector<Point3f> vertices;
  vector<Point3f> normals;
  vector<Point3f> faces;
};

MeshData readInput(const char* filename) {
  MeshData mesh;
  ifstream file(filename);
  string line;

  vector<Point3f> vertices;
  vector<Point3f> normals;
  vector<Point3f> faces;

  MeshData it;
  while (getline(file, line)) {
    float x, y, z;
		float u, v, w;
    string token = line.c_str();
    // std::cout << token[0] << std::endl;
    switch(line.c_str()[0]) {
      case 'v':
				if (token[1] == 'n') {
					sscanf(line.c_str(), "n %f %f %f", &x, &y, &z);
					normals.push_back(new Point3f(x, y, z));
				} else {
					sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
					vertices.push_back(new Point3f(x, y, z));
				}
				break;
      case 'f':
        sscanf(line.c_str(), "f %f//%f %f//%f %f//%f", &x, &u, &y, &v, &z, &w);
				auto face = new Point3f(x, y, z);
				face->log();
        faces.push_back(face);
        break;
    }
  }

  mesh.vertices = vertices;
  mesh.normals = normals;
  mesh.faces = faces;

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

    MeshData mesh = readInput("../meshes/teapot.obj");
    std::cout << "Nr. of vertices extracted: " << mesh.vertices.size() << std::endl;
    std::cout << "Nr. of normals extracted: " << mesh.normals.size() << std::endl;
    std::cout << "Nr. of faces extracted: " << mesh.faces.size() << std::endl;

    Renderer renderer(scene);
    renderer.render(threadCount, spp);

    return 0;
}
