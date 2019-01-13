#include "intersectable.h"
#include "hitRecord.h"

#ifndef IMATERIAL_H
#define IMATERIAL_H

class LightGeometry : public Intersectable {
  public:
    virtual HitRecord* sample() = 0;
};
#endif
