#include "logger.h"
#include <stdio.h>
#include <iostream>
#include "hitRecord.h"
#include "intersectables/meshTriangle.h"
#include "intersectables/triangle.h"
#include "math/matrix3f.h"
#include "math/matrix4f.h"
#include "math/vector3f.h"
#include "math/vector4f.h"
#include "objReader.h"
#include "ray.h"
#include "spectrum.h"

void Logger::log(const Vector3f& v) { printf("(%f, %f, %f)\n", v.x, v.y, v.z); }

void Logger::log(const Vector4f& v) { printf("(%f, %f, %f, %f)\n", v.x, v.y, v.z, v.w); }

void Logger::log(const Matrix3f& m) {
  printf("%f, %f, %f\n%f, %f, %f\n%f, %f, %f\n", m.m00, m.m01, m.m02, m.m10, m.m11, m.m12, m.m20,
         m.m21, m.m22);
}

void Logger::log(const Matrix4f& m) {
  printf("%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n", m.m00, m.m01, m.m02,
         m.m03, m.m10, m.m11, m.m12, m.m13, m.m20, m.m21, m.m22, m.m23, m.m30, m.m31, m.m32, m.m33);
}

void Logger::log(const Spectrum& s) { printf("(%f, %f, %f)\n", s.r, s.g, s.b); }

void Logger::log(const HitRecord& hit) {
  std::cout << hit.t << std::endl;
  Logger().log(*hit.position);
  Logger().log(*hit.normal);
  Logger().log(*hit.tangent);
  Logger().log(*hit.wIn);
}

void Logger::log(const Ray& ray) {
  Logger().log(*ray.origin);
  Logger().log(*ray.direction);

  printf("(%i, %i, %i)\n", ray.i, ray.j, ray.depth);
}

void Logger::log(const Triangle& triangle) {
  std::cout << "face-index: " << triangle.getFaceId() << std::endl;
  std::cout << "vertices: " << std::endl;
  Logger().log(triangle.getVertexA());
  Logger().log(triangle.getVertexB());
  Logger().log(triangle.getVertexC());
}

void Logger::log(const MeshTriangle& triangle) {
  std::cout << "face-index: " << triangle.getFaceId() << std::endl;
  std::cout << "vertices: " << std::endl;
  Logger().log(triangle.getVertexA());
  Logger().log(triangle.getVertexB());
  Logger().log(triangle.getVertexC());

  std::cout << "normals: " << std::endl;
  Logger().log(triangle.getVertexA());
  Logger().log(triangle.getVertexB());
  Logger().log(triangle.getVertexC());
}

void Logger::log(const MeshData& md) {
  std::cout << "Vertices extracted: " << md.vertices.size() << std::endl;
  std::cout << "Normals extracted: " << md.normals.size() << std::endl;
  std::cout << "Faces extracted: " << md.faces.size() << std::endl;
  std::cout << "Normal Faces extracted: " << md.normalFaces.size() << std::endl;
}
