#include <random>
#include <vector>
#include "samplers/randomSampler.h"

RandomSampler::RandomSampler() {}

std::vector<std::vector<float>*>* RandomSampler::makeSample(int n, int d) {
  std::vector<std::vector<float>* >* result = new std::vector<std::vector<float>*>();
  for (int i = 0; i < n; i++) {
    std::vector<float>* samples = new std::vector<float>();
    for (int j = 0; j < d; j++) {
      float num = (double)rand() / RAND_MAX;
      samples->push_back(num);
    }
    result->push_back(samples);
  }

  return result;
}
