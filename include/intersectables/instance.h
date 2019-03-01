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

    // transformation matrix T
    Matrix4f* transformation;

    // inverse transformation T^-1
    Matrix4f* invTransformation;

    // denotes (T^-1)^t used to transform normals and tangent vectors
    Matrix4f* invTrasnposedTransformation;

  public:
    Instance(Intersectable*);
    Instance(Intersectable*, Matrix4f*);
    ~Instance();

    HitRecord* intersect(Ray* ray);
};

#endif
