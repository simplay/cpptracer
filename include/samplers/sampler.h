#ifndef SAMPLER_H
#define SAMPLER_H

#include <vector>

class Sampler {
 public:
  virtual std::vector<std::vector<float>*>* makeSample(int, int) = 0;
};
#endif
