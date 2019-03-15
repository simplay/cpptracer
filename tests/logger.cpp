#include "logger.h"
#include <gtest/gtest.h>
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

TEST(Logger, log_vector3f) { Logger().log(Vector3f()); }

TEST(Logger, log_vector4f) { Logger().log(Vector4f()); }

TEST(Logger, log_spectrum) { Logger().log(Spectrum(1, 1, 1)); }

TEST(Logger, log_matrix3f) { Logger().log(Matrix3f()); }

TEST(Logger, log_matrix4f) { Logger().log(Matrix3f()); }

TEST(Logger, log_ray) {
  Ray ray(new Vector3f(), new Vector3f());
  Logger().log(ray);
}

TEST(Logger, log_hitrecord) {
  auto diffuse = new Diffuse(new Spectrum(0.0));
  auto shape = new Sphere(diffuse, Vector3f(0.0, 0, 0), 0.5);
  HitRecord hit(1, new Vector3f(), new Vector3f(), new Vector3f(), new Vector3f(), diffuse, shape);
  Logger().log(hit);
}

TEST(Logger, log_triangle) {
  auto material = new Diffuse(new Spectrum(0.0));
  auto tri = Triangle(1, material, Vector3f(0.0, 0.0, 0.0), Vector3f(1.0, 0.0, 0.0),
                      Vector3f(0.0, 1.0, 0.0));

  Logger().log(tri);
}

TEST(Logger, log_mesh_triangle) {
  auto material = new Diffuse(new Spectrum(0.0));
  auto tri = MeshTriangle(1, material, Vector3f(0.0, 0.0, 0.0), Vector3f(1.0, 0.0, 0.0),
                          Vector3f(0.0, 1.0, 0.0), Vector3f(0.0, 1.0, 0.0), Vector3f(0.0, 1.0, 0.0),
                          Vector3f(0.0, 1.0, 0.0));

  Logger().log(tri);
}

TEST(Logger, log_mesh_data) {
  MeshData md;
  Logger().log(md);
}
