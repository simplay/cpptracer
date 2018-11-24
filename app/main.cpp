#include <iostream>
#include <stdlib.h>

#include "exampleConfig.h"
#include "point3f.h"

int main() {
  std::cout << "C++ Raytracer v"
            << PROJECT_VERSION_MAJOR
            << "."
            << PROJECT_VERSION_MINOR
            << std::endl;

  Point3f d = Point3f(5, 1, 3);
  std::cout << "Dot product is:" << d.dot() << std::endl;
  return 0;
}