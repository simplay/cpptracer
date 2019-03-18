#include "logger.h"
#include <gtest/gtest.h>
#include <iostream>
#include "hitRecord.h"
#include "intersectables/meshTriangle.h"
#include "intersectables/sphere.h"
#include "intersectables/triangle.h"
#include "materials/diffuse.h"
#include "math/matrix3f.h"
#include "math/matrix4f.h"
#include "math/vector3f.h"
#include "math/vector4f.h"
#include "objReader.h"
#include "ray.h"
#include "spectrum.h"

TEST(Logger, log_vector3f) {
  auto vec = Vector3f(1, 2, 3);
  Logger().log(vec);
  ASSERT_EQ("(1, 2, 3)", Logger().toString(vec));
}

TEST(Logger, log_vector4f) {
  auto vec = Vector4f(1, 2, 3, 4);
  Logger().log(vec);
  ASSERT_EQ("(1, 2, 3, 4)", Logger().toString(vec));
}

TEST(Logger, log_spectrum) {
  auto s = Spectrum(0.25, 0.5, 1);
  Logger().log(s);
  ASSERT_EQ("(0.25, 0.5, 1)", Logger().toString(s));
}

TEST(Logger, log_matrix3f) {
  auto m = Matrix3f(1, 2, 3, 4, 5, 6, 7, 8, 9);
  Logger().log(m);
  ASSERT_EQ("(\n1 2 3\n4 5 6\n7 8 9\n)", Logger().toString(m));
}

TEST(Logger, log_matrix4f) {
  auto m = Matrix4f(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
  Logger().log(m);
  ASSERT_EQ("(\n1 2 3 4\n5 6 7 8\n9 10 11 12\n13 14 15 16\n)", Logger().toString(m));
}

TEST(Logger, log_ray) {
  Ray ray(new Vector3f(), new Vector3f());
  std::ostringstream oss;
  oss << "origin: " << Logger().toString(*ray.origin) << std::endl
      << "direction: " << Logger().toString(*ray.direction) << std::endl
      << "(i, j): "
      << "(" << ray.i << ", " << ray.j << ")" << std::endl
      << "depth: " << ray.depth;

  Logger().log(ray);
  ASSERT_EQ(oss.str(), Logger().toString(ray));
}

TEST(Logger, log_hitrecord) {
  auto diffuse = new Diffuse(new Spectrum(0.0));
  auto shape = new Sphere(diffuse, Vector3f(0.0, 0, 0), 0.5);
  HitRecord hit(1, new Vector3f(), new Vector3f(), new Vector3f(), new Vector3f(), diffuse, shape);

  std::ostringstream oss;
  oss << "t: " << hit.t << std::endl
      << "position: " << Logger().toString(*hit.position) << std::endl
      << "normal: " << Logger().toString(*hit.normal) << std::endl
      << "tangent: " << Logger().toString(*hit.tangent) << std::endl
      << "wIn: " << Logger().toString(*hit.wIn);

  Logger().log(hit);
  ASSERT_EQ(oss.str(), Logger().toString(hit));
}

TEST(Logger, log_triangle) {
  auto material = new Diffuse(new Spectrum(0.0));
  auto triangle = Triangle(1, material, Vector3f(0.0, 0.0, 0.0), Vector3f(1.0, 0.0, 0.0),
                           Vector3f(0.0, 1.0, 0.0));

  std::ostringstream oss;
  oss << "face-index: " << triangle.getFaceId() << std::endl
      << "vertices: " << std::endl
      << Logger().toString(triangle.getVertexA()) << std::endl
      << Logger().toString(triangle.getVertexB()) << std::endl
      << Logger().toString(triangle.getVertexC());
  Logger().log(triangle);
  ASSERT_EQ(oss.str(), Logger().toString(triangle));
}

TEST(Logger, log_mesh_triangle) {
  auto material = new Diffuse(new Spectrum(0.0));
  auto triangle = MeshTriangle(1, material, Vector3f(0.0, 0.0, 0.0), Vector3f(1.0, 0.0, 0.0),
                               Vector3f(0.0, 1.0, 0.0), Vector3f(0.0, 1.0, 0.0),
                               Vector3f(0.0, 1.0, 0.0), Vector3f(0.0, 1.0, 0.0));

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

  Logger().log(triangle);
  ASSERT_EQ(oss.str(), Logger().toString(triangle));
}

TEST(Logger, log_mesh_data) {
  MeshData md;
  std::ostringstream oss;
  oss << "Vertices extracted: " << md.vertices.size() << std::endl
      << "Normals extracted: " << md.normals.size() << std::endl
      << "Faces extracted: " << md.faces.size() << std::endl
      << "Normal Faces extracted: " << md.normalFaces.size();

  Logger().log(md);
  ASSERT_EQ(oss.str(), Logger().toString(md));
}
