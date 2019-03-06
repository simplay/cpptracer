#include <stdio.h>

class Vector3f;

#ifndef VECTOR4F_H
#define VECTOR4F_H

class Vector4f {
  public:
    float x;
    float y;
    float z;
    float w;

    Vector4f();
    Vector4f(float, float, float, float);
    Vector4f(Vector3f*, float);

    float dot(Vector4f* other);
    void log() {
      printf("(%f, %f, %f, %f)\n", x, y, z, w);
    }

    Vector3f* toVector3f();
};

#endif
