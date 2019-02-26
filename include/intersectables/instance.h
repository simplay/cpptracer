#include "intersectable.h"
#include "../math/matrix4f.h"
#include "../math/point3f.h"
#include "../hitRecord.h"
#include "../ray.h"

class Material;

#ifndef INSTANCE_H
#define INSTANCE_H

class Instance : public Intersectable {
  private:
    Intersectable* intersectable;
    Matrix4f* transformation;
    Matrix4f* invTransformation;

  public:
    Instance(Intersectable*, Matrix4f*);

    HitRecord* intersect(Ray* ray);
};

#endif
