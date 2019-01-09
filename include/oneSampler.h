#include <vector>

#ifndef ONE_SAMPLER_H
#define ONE_SAMPLER_H

class OneSampler {
  public:
    OneSampler();
    std::vector<std::vector<float>> makeSample(int, int);
};

#endif
