#include <iostream>
#include <stdlib.h>
#include "exampleConfig.h"
#include "point3f.h"
#include <stdio.h>
#include <string.h>
#include <image.h>
#include <thread>

using namespace std;

void doSomething(int id) {
    cout << "Thread id = " << id << endl;
}

/**
 * Spawns n threads
 */
void spawnThreads(int n)
{
    thread threads[n];
    // spawn n threads:
    for (int i = 0; i < n; i++) {
        threads[i] = thread(doSomething, i + 1);
    }

    for (auto& th : threads) {
        th.join();
    }
}

int main(int argc, char *argv[]) {
    std::cout << "C++ Raytracer v"
            << PROJECT_VERSION_MAJOR
            << "."
            << PROJECT_VERSION_MINOR
            << std::endl;


    Image img = Image(500, 500);
    img.print();

    spawnThreads(5);

    return 0;
}
