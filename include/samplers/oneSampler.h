#ifndef ONE_SAMPLER_H
#define ONE_SAMPLER_H

#include <vector>
#include "sampler.h"

class OneSampler : public Sampler {
 public:
  OneSampler();
  std::vector<std::vector<float>*>* makeSample(int, int);
};
#endif
