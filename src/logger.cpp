#include "logger.h"
#include <sstream>
#include "hitRecord.h"
#include "intersectables/geometries/meshTriangle.h"
#include "intersectables/geometries/triangle.h"
#include "math/matrix3f.h"
#include "math/matrix4f.h"
#include "math/vector3f.h"
#include "math/vector4f.h"
#include "objReader.h"
#include "ray.h"
#include "spectrum.h"

std::string Logger::toString(const Vector3f& v) {
  std::ostringstream oss;
  oss << "(" << v.x << ", " << v.y << ", " << v.z << ")";
  return oss.str();
}

std::string Logger::toString(const Vector4f& v) {
  std::ostringstream oss;
  oss << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
  return oss.str();
}

std::string Logger::toString(const Matrix3f& m) {
  std::ostringstream oss;
  oss << "(" << std::endl
      << m.m00 << " " << m.m01 << " " << m.m02 << std::endl
      << m.m10 << " " << m.m11 << " " << m.m12 << std::endl
      << m.m20 << " " << m.m21 << " " << m.m22 << std::endl
      << ")";
  return oss.str();
}

std::string Logger::toString(const Matrix4f& m) {
  std::ostringstream oss;
  oss << "(" << std::endl
      << m.m00 << " " << m.m01 << " " << m.m02 << " " << m.m03 << std::endl
      << m.m10 << " " << m.m11 << " " << m.m12 << " " << m.m13 << std::endl
      << m.m20 << " " << m.m21 << " " << m.m22 << " " << m.m23 << std::endl
      << m.m30 << " " << m.m31 << " " << m.m32 << " " << m.m33 << std::endl
      << ")";
  return oss.str();
}

std::string Logger::toString(const Spectrum& s) {
  std::ostringstream oss;
  oss << "(" << s.r << ", " << s.g << ", " << s.b << ")";
  return oss.str();
}

std::string Logger::toString(const HitRecord& hit) {
  std::ostringstream oss;
  oss << "t: " << hit.t << std::endl
      << "position: " << Logger().toString(*hit.position) << std::endl
      << "normal: " << Logger().toString(*hit.normal) << std::endl
      << "tangent: " << Logger().toString(*hit.tangent) << std::endl
      << "wIn: " << Logger().toString(*hit.wIn);

  return oss.str();
}

std::string Logger::toString(const Ray& ray) {
  std::ostringstream oss;
  oss << "origin: " << Logger().toString(*ray.origin) << std::endl
      << "direction: " << Logger().toString(*ray.direction) << std::endl
      << "(i, j): "
      << "(" << ray.i << ", " << ray.j << ")" << std::endl
      << "depth: " << ray.depth;

  return oss.str();
}

std::string Logger::toString(const Triangle& triangle) {
  std::ostringstream oss;
  oss << "face-index: " << triangle.getFaceId() << std::endl
      << "vertices: " << std::endl
      << Logger().toString(triangle.getVertexA()) << std::endl
      << Logger().toString(triangle.getVertexB()) << std::endl
      << Logger().toString(triangle.getVertexC());

  return oss.str();
}

std::string Logger::toString(const MeshTriangle& triangle) {
  std::ostringstream oss;
  oss << "face-index: " << triangle.getFaceId() << std::endl
      << "vertices: " << std::endl
      << Logger().toString(triangle.getVertexA()) << std::endl
      << Logger().toString(triangle.getVertexB()) << std::endl
      << Logger().toString(triangle.getVertexC()) << std::endl
      << "normals: " << std::endl
      << Logger().toString(triangle.getNormalA()) << std::endl
      << Logger().toString(triangle.getNormalB()) << std::endl
      << Logger().toString(triangle.getNormalC());

  return oss.str();
}

std::string Logger::toString(const MeshData& md) {
  std::ostringstream oss;
  oss << "Vertices extracted: " << md.vertices.size() << std::endl
      << "Normals extracted: " << md.normals.size() << std::endl
      << "Faces extracted: " << md.faces.size() << std::endl
      << "Normal Faces extracted: " << md.normalFaces.size();

  return oss.str();
}

std::string Logger::toString(const std::string& str) { return str; }
