// usage: ./main.x IMG_DIM

#include <iostream>
#include <stdlib.h>
#include "exampleConfig.h"
#include "point3f.h"
#include "film.h"
#include <stdio.h>
#include <string.h>
#include "spectrum.h"
#include <image.h>
#include <thread>
#include <algorithm>
#include <vector>
#include "camera.h"
#include "oneSampler.h"
#include "scene.h"
#include "pointLightIntegrator.h"
#include "renderTask.h"

using namespace std;

void computeContribution(RenderTask* renderTask) {
  for (vector<int>::iterator it = (*renderTask->indices).begin(); it != (*renderTask->indices).end(); ++it) {
    // samples = integrator.make_pixel_samples(sampler, scene.spp);
    OneSampler os;
    auto samples = os.makeSample(1, 2);
    for (unsigned k = 0; k < samples.size(); k++) {
      auto sample = samples.at(k);

      // 2d image coordinates
      int ii = *it / renderTask->width;
      int jj = *it % renderTask->height;

      int x = ii;
      int y = (renderTask->height - 1) - jj;

      // TODO remove
      // float r = ((float) ii / (renderTask.film.width()));
      // float g = ((float) jj / (renderTask.film.height()));
      // float shift = ((float)(ii + jj)) / (renderTask.film.width() + renderTask.film.height());
      // float b = (1 - shift);
      // Spectrum s = Spectrum(r, g, b);

      Ray* ray = renderTask->scene->camera->makeWorldspaceRay(ii, jj, sample);
      Spectrum* raySpectrum = renderTask->scene->integrator->integrate(ray);
      renderTask->scene->film->addSample(x + sample.at(0), y + sample.at(1), raySpectrum);
    }
  }
}

// spawns n threads
void runRenderer(int n, Scene* scene) {
    thread threads[n];
    vector<int> indexLists[n];
    vector<int> indexValues;

    int height = scene->film->height();
    int width = scene->film->width();

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
      RenderTask* rt = new RenderTask(
          width, height, &indexLists[i], scene
      );
      threads[i] = thread(computeContribution, rt);
    }

    for (auto& th : threads) {
      th.join();
    }

    Image img = Image(width, height, scene->film->measurements());
    img.print();
}

int main(int argc, char *argv[]) {
    cout << "C++ Raytracer v"
         << PROJECT_VERSION_MAJOR
         << "."
         << PROJECT_VERSION_MINOR
         << endl;

    int dim = 400;
    if (argc > 1) {
      dim = std::atoi(argv[1]);
    }

    unsigned threadCount = thread::hardware_concurrency();
    cout << "Using " << threadCount << " threads" << endl;

    // don't hard-code these values, read from argv
    Scene* scene = new Scene(dim, dim);

    runRenderer(threadCount, scene);

    return 0;
}
