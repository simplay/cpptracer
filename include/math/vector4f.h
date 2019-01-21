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
    float dot(Vector4f* other);
};

#endif
