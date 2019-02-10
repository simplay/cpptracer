#include <vector>
#include "oneSampler.h"

OneSampler::OneSampler() {}

std::vector<std::vector<float>> OneSampler::makeSample(int, int d) {
  std::vector<float> samples;
  for (int k = 0; k < d; k++) {
    samples.push_back(0.5);
  }

  std::vector<std::vector<float>> result{samples};
  return result;
}
