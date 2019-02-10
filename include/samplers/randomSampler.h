#include <vector>
#include "sampler.h"

#ifndef RANDOM_SAMPLER_H
#define RANDOM_SAMPLER_H

class RandomSampler : public Sampler {
  public:
    RandomSampler();
    std::vector<std::vector<float>*>* makeSample(int, int);
};

#endif
