#include <algorithm>
#include <thread>
#include <vector>
#include <chrono>
#include <iostream>
#include "renderer.h"
#include "renderTask.h"
#include "samplers/sampler.h"
#include "samplers/oneSampler.h"
#include "ray.h"
#include "spectrum.h"
#include "image.h"
#include "integrators/pointLightIntegrator.h"
#include "progressBar.h"

using namespace std;

Renderer::Renderer(Scene* scene): scene(scene) {}

void Renderer::computeContribution(int id, RenderTask* renderTask, vector<int>* taskCounters) {
  // for each image index value
  for (vector<int>::iterator idxValue = (*renderTask->indices).begin(); idxValue != (*renderTask->indices).end(); ++idxValue) {
    auto samples = renderTask->scene->sampler->makeSample(renderTask->spp, 2);

    // for each sample index
    for (unsigned sampleIdx = 0; sampleIdx < samples->size(); sampleIdx++) {
      auto sample = samples->at(sampleIdx);

      // compute 2D image lookup coordinates (rowIdx, colIdx) from 1D index value *idxValue
      int rowIdx = *idxValue / renderTask->width;
      int colIdx = *idxValue % renderTask->width;

      Ray* ray = renderTask->scene->camera->makeWorldspaceRay(rowIdx, colIdx, sample);
      Spectrum* raySpectrum = renderTask->scene->integrator->integrate(ray);

      // consider coordinates in between pixel locations
      // store in row-first order
      renderTask->scene->film->addSample(rowIdx + sample->at(0), colIdx + sample->at(1), raySpectrum);

      taskCounters->at(id)++;
      delete ray->origin;
      delete ray->direction;
      delete ray;
      delete raySpectrum;
      delete sample;
    }

    delete samples;
  }
  delete renderTask;
}

// Spawns a given number of threads that render the given scene in parallel.
// Writes the result to an image.
void Renderer::render(int threadCount, int spp) {
  thread threads[threadCount];
  vector<vector<int>>* indexLists = new vector<vector<int>>(threadCount);
  vector<int>* taskCounters = new vector<int>(threadCount);

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
  for (int id = 0; id < threadCount; id++) {
    RenderTask* rt = new RenderTask(
      width, height, &indexLists->at(id), scene, spp
    );

    threads[id] = thread(&Renderer::computeContribution, this, id, rt, taskCounters);
  }

  int totalTasks = width * height * spp;
  ProgressBar progressBar(taskCounters, totalTasks);
  progressBar.start();

  // wait until all threads have completed their task
  for (auto& threads : threads) {
    threads.join();
  }
  progressBar.stop();

  // write computed contribution to image and save it
  Image img = Image(width, height, scene->film->normalMeasurements(), scene->filename());
  img.print();
}
