#ifndef VECTOR4F_H
#define VECTOR4F_H

class Vector4f {
  float _x, _y, _z, _w;

  public:

  Vector4f();
  Vector4f(float, float, float, float);

  float x();
  float y();
  float z();
  float w();

  float dot(Vector4f other);
};

#endif
