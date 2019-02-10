#include <vector>

#ifndef SAMPLER_H
#define SAMPLER_H

class Sampler {
  public:
    virtual std::vector<std::vector<float>> makeSample(int, int) = 0;
};

#endif
