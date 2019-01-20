// usage:
//  ./main.x IMG_DIM
//  ./main.x IMG_WIDTH IMG_HEIGHT

#include "exampleConfig.h"
#include <iostream>
#include <thread>
#include "renderer.h"

using namespace std;

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

    if (argc == 2) {
      width = std::atoi(argv[1]);
      height = width;
    } else if (argc == 3) {
      width = std::atoi(argv[1]);
      height = std::atoi(argv[2]);
    }

    unsigned threadCount = thread::hardware_concurrency();
    cout << "Using " << threadCount << " threads" << endl;

    Scene* scene = new Scene(width, height);
    Renderer* renderer = new Renderer(scene);
    renderer->render(threadCount);

    return 0;
}
