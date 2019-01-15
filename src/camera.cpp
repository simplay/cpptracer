#include "camera.h"
#include "point3f.h"
#include "vector4f.h"
#include <math.h>
#include "ray.h"

Camera::Camera(
  Point3f* eye,
  Point3f* lookAt,
  Point3f* up,
  float fov,
  float aspectRatio,
  float width,
  float height
) :
  eye(eye),
  lookAt(lookAt),
  up(up),
  fov(fov),
  aspectRatio(aspectRatio),
  width(width),
  height(height)
{
  Point3f* from = new Point3f(eye);
  Point3f* to = new Point3f(lookAt);
  Point3f* upCopy = new Point3f(up);

  // z-axis
  Point3f* w = new Point3f(from);
  w->sub(to);
  w->normalize();
  Vector4f* zc = new Vector4f(w->x, w->y, w->z, 0.0);

  // # x-axis
  Point3f* u = upCopy->cross(w);
  u->normalize();
  Vector4f* xc = new Vector4f(u->x, u->y, u->z, 0.0);

  // # y-axis
  Point3f* v = w->cross(u);
  Vector4f* yc = new Vector4f(v->x, v->y, v->z, 0.0);
  Vector4f* e = new Vector4f(from->x, from->y, from->z, 1.0);

  matrix = new Matrix4f(xc, yc, zc, e);

  // compute image corners
  double angularFov = M_PI * (fov / 180.0);
  top = tanf(angularFov / 2.0);
  bottom = -top;
  right = aspectRatio * top;
  left = -right;
}

Matrix4f* Camera::transformation() {
  return this->matrix;
}

// Given a ray in image space, make a ray in world space according to the
// camera specifications. The method receives a sample that the camera can use
// to generate the ray. Typically the first two sample dimensions are used to
// sample a location in the current pixel. The samples are assumed to be in
// the range [0,1].
//
// @param i pixel column index: Integer, start counting at 1
// @param j pixel row index: Integer, start counting at 1
// @param sample random sample that the camera can use to generate a ray float
//   array.
// @return the ray in world coordinates
Ray* Camera::makeWorldspaceRay(int i, int j, std::vector<float> samples) {
  float s1 = samples.at(0);
  float s2 = samples.at(1);
  float u_ij = left + (right - left) * ((i - 1) + s1) / width;
  float v_ij = bottom + (top - bottom) * ((j - 1) + s2) / height;
  float w_ij = -1.0;
  Vector4f* v = new Vector4f(u_ij, v_ij, w_ij, 0);

  Vector4f* p_uvw = matrix->mult(v);
  float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
  return new Ray(new Point3f(eye), new Point3f(p_uvw), r);
}
