#include <iostream>
#include <stdlib.h>
#include "exampleConfig.h"
#include "point3f.h"
#include "film.h"
#include <stdio.h>
#include <string.h>
#include <image.h>
#include <thread>
#include <algorithm>
#include <vector>

using namespace std;

struct render_task {
  vector<int> indices;
  int width;
  int height;
  // Scene scene;
};

void computeContribution(int id, render_task renderTask) {
  for (vector<int>::iterator it = renderTask.indices.begin(); it != renderTask.indices.end(); ++it) {
    // 2d image coordinates
    int ii = *it / renderTask.width;
    int jj = *it % renderTask.height;

    // TODO compute contribution
    // ray = renderTask.scene.camera.make_world_space_ray(ii, jj, samples[k-1])
    // ray_spectrum = integrator.integrate(ray)

    // write to film
    // scene.film.add_sample(
    //     ii + samples[k-1][0].to_f,
    //     jj + samples[k-1][1].to_f,
    //     ray_spectrum
    //  )
  }
}

// spawns n threads
void runRenderer(int n, Film film) {
    thread threads[n];
    vector<int> indexLists[n];
    vector<int> indexValues;

    int height = film.height();
    int width = film.width();

    // initialize a vector that contains all 1d image coordinates
    for (int i = 0; i < width * height; ++i) {
      indexValues.push_back(i);
    }

    // permutate image coordiantes
    random_shuffle(indexValues.begin(), indexValues.end());

    // assign image coordinates to tasks
    int counter = 0;
    for (vector<int>::iterator it=indexValues.begin(); it != indexValues.end(); ++it) {
      indexLists[counter % n].push_back(*it);
      counter++;
    }

    // spawn n threads:
    for (int i = 0; i < n; i++) {
      render_task rt = render_task();
      rt.width = width;
      rt.height = height;
      rt.indices = indexLists[i];
      threads[i] = thread(computeContribution, i + 1, rt);
    }

    for (auto& th : threads) {
      th.join();
    }

    Image img = Image(width, height, film.measurements());
    img.print();
}

int main(int argc, char *argv[]) {
    cout << "C++ Raytracer v"
         << PROJECT_VERSION_MAJOR
         << "."
         << PROJECT_VERSION_MINOR
         << endl;

    //BoxFilterFilm film = BoxFilterFilm();

    // don't hard-code these values, read from argv
    int threadCount = 5;
    int width = 500;
    int height = 500;

    Film film = Film(width, height);

    runRenderer(threadCount, film);

    return 0;
}
