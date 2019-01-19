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
  // for each image index value
  for (vector<int>::iterator idxValue = (*renderTask->indices).begin(); idxValue != (*renderTask->indices).end(); ++idxValue) {
    OneSampler* os = new OneSampler();
    auto samples = os->makeSample(1, 2);

    // for each sample index
    for (unsigned sampleIdx = 0; sampleIdx < samples.size(); sampleIdx++) {
      auto sample = samples.at(sampleIdx);

      // compute 2d image lookup coordinates (i, j) from 1d index value *idx
      int rowIdx = *idxValue / renderTask->width;
      int colIdx = *idxValue % renderTask->width;

      // int x = ii;
      // int y = renderTask->width - jj - 1;

      Ray* ray = renderTask->scene->camera->makeWorldspaceRay(rowIdx, colIdx, sample);
      Spectrum* raySpectrum = renderTask->scene->integrator->integrate(ray);

      // consider coordinates in between pixel locations
      // store in row-first order
      renderTask->scene->film->addSample(rowIdx + sample.at(0), colIdx + sample.at(1), raySpectrum);
    }
  }
}

// spawns n threads
void runRenderer(int n, Scene* scene) {
  thread threads[n];
  // vector<int> indexLists[n];
  vector<vector<int>>* indexLists = new vector<vector<int>>(n);
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
    indexLists->at(counter % n).push_back(*it);
    counter++;
  }

  // spawn n threads:
  for (int i = 0; i < n; i++) {
    RenderTask* rt = new RenderTask(
      width, height, &indexLists->at(i), scene
    );
    threads[i] = thread(computeContribution, rt);
  }

  for (auto& th : threads) {
    th.join();
  }

  Image img = Image(width, height, scene->film->normalMeasurements());
  img.print();
}

int main(int argc, char *argv[]) {
    cout << "C++ Raytracer v"
         << PROJECT_VERSION_MAJOR
         << "."
         << PROJECT_VERSION_MINOR
         << endl;

    int dimX = 400;
    int dimY = 400;

    if (argc == 2) {
      dimX = std::atoi(argv[1]);
      dimY = dimX;
    } else if (argc == 3) {
      dimX = std::atoi(argv[1]);
      dimY = std::atoi(argv[2]);
    }

    unsigned threadCount = thread::hardware_concurrency();
    cout << "Using " << threadCount << " threads" << endl;

    // don't hard-code these values, read from argv
    Scene* scene = new Scene(dimX, dimY);

    runRenderer(threadCount, scene);

    return 0;
}
