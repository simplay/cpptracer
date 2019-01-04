#include <iostream>
#include <stdlib.h>
#include "exampleConfig.h"
#include "point3f.h"
#include <stdio.h>
#include <string.h>
#include <image.h>

int main(int argc, char *argv[]) {
    std::cout << "C++ Raytracer v"
            << PROJECT_VERSION_MAJOR
            << "."
            << PROJECT_VERSION_MINOR
            << std::endl;

    Image img = Image(500, 500);
    img.print();

    return 0;
}
