// usage:
//  ./main.x IMG_DIM
//  ./main.x IMG_WIDTH IMG_HEIGHT

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

      // compute 2D image lookup coordinates (rowIdx, colIdx) from 1D index value *idxValue
      int rowIdx = *idxValue / renderTask->width;
      int colIdx = *idxValue % renderTask->width;

      Ray* ray = renderTask->scene->camera->makeWorldspaceRay(rowIdx, colIdx, sample);
      Spectrum* raySpectrum = renderTask->scene->integrator->integrate(ray);

      // consider coordinates in between pixel locations
      // store in row-first order
      renderTask->scene->film->addSample(rowIdx + sample.at(0), colIdx + sample.at(1), raySpectrum);
    }
  }
}

// Spawns a given number of threads that render the given scene in parallel.
// Writes the result to an image.
void runRenderer(int threadCount, Scene* scene) {
  thread threads[threadCount];
  vector<vector<int>>* indexLists = new vector<vector<int>>(threadCount);
  vector<int> indexValues;

  int height = scene->film->height;
  int width = scene->film->width;

  // initialize a vector that contains all 1D image coordinates. I.e. store the
  // numbers (0..pixelcount - 1)
  for (int index = 0; index < width * height; ++index) {
    indexValues.push_back(index);
  }

  // Permutate image coordiantes so that every thread receives random image locations.
  random_shuffle(indexValues.begin(), indexValues.end());

  // Equally assign each indexList random 1D image indices.
  int counter = 0;
  for (vector<int>::iterator it=indexValues.begin(); it != indexValues.end(); ++it) {
    indexLists->at(counter % threadCount).push_back(*it);
    counter++;
  }

  // spawn threadCount threads:
  for (int i = 0; i < threadCount; i++) {
    RenderTask* rt = new RenderTask(
      width, height, &indexLists->at(i), scene
    );
    threads[i] = thread(computeContribution, rt);
  }

  // wait until all threads have completed their task
  for (auto& threads : threads) {
    threads.join();
  }

  // write computed contribution to image and save it
  Image img = Image(width, height, scene->film->normalMeasurements());
  img.print();
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
    runRenderer(threadCount, scene);

    return 0;
}
