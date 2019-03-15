#ifndef LOGGER_H
#define LOGGER_H

class Vector3f;
class Vector4f;
class Matrix3f;
class Matrix4f;
class Spectrum;
class HitRecord;
class Ray;
class Triangle;
class MeshTriangle;
class MeshData;

class Logger {
 public:
  void static log(const Vector3f&);
  void static log(const Vector4f&);
  void static log(const Matrix3f&);
  void static log(const Matrix4f&);
  void static log(const Spectrum&);
  void static log(const HitRecord&);
  void static log(const Ray&);
  void static log(const Triangle&);
  void static log(const MeshTriangle&);
  void static log(const MeshData&);
};
#endif
