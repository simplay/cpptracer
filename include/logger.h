#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>

class Vector3f;
class Vector4f;
class Matrix3f;
class Matrix4f;
class Spectrum;
class HitRecord;
class Ray;
class Triangle;
class MeshTriangle;
struct MeshData;

class Logger {
 public:
  std::string static toString(const Vector3f&);
  std::string static toString(const Vector4f&);
  std::string static toString(const Matrix3f&);
  std::string static toString(const Matrix4f&);
  std::string static toString(const Spectrum&);
  std::string static toString(const HitRecord&);
  std::string static toString(const Ray&);
  std::string static toString(const Triangle&);
  std::string static toString(const MeshTriangle&);
  std::string static toString(const MeshData&);
  std::string static toString(const std::string&);

  template <typename Loggable>
  inline void log(const Loggable& l) {
    std::cout << toString(l);
  }
};
#endif
