#include <vector>
#include "samplers/oneSampler.h"

OneSampler::OneSampler() {}

std::vector<std::vector<float>*>* OneSampler::makeSample(int, int d) {
  std::vector<std::vector<float>* >* result = new std::vector<std::vector<float>*>();
  std::vector<float>* samples = new std::vector<float>();
  for (int k = 0; k < d; k++) {
    samples->push_back(0.5);
  }
  result->push_back(samples);

  return result;
}
