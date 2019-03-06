#include <math.h>
#include <iostream>
#include "camera.h"
#include "ray.h"
#include "math/vector3f.h"
#include "math/vector4f.h"

Camera::Camera(
  Vector3f* eye,
  Vector3f* lookAt,
  Vector3f* up,
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
  Vector3f from(eye);
  Vector3f to(lookAt);

  // z-axis
  Vector3f w(from);
  w.sub(&to);
  w.normalize();
  Vector4f* zc = new Vector4f(w.x, w.y, w.z, 0.0);

  // # x-axis
  Vector3f* u = up->cross(&w);
  u->normalize();
  Vector4f* xc = new Vector4f(u->x, u->y, u->z, 0.0);

  // # y-axis
  Vector3f* v = w.cross(u);
  Vector4f* yc = new Vector4f(v->x, v->y, v->z, 0.0);
  delete v;
  delete u;

  Vector4f* e = new Vector4f(from.x, from.y, from.z, 1.0);

  matrix = new Matrix4f(xc, yc, zc, e, false);

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

/**
 * Given a ray in image space, make a ray in world space according to the
 * camera specifications. The method receives a sample that the camera can use
 * to generate the ray. Typically the first two sample dimensions are used to
 * sample a location in the current pixel. The samples are assumed to be in
 * the range [0,1].
 *
 * @param i row index, start counting at 0.
 * @param j column index, start counting at 0
 * @param random sample that the camera can use to generate a ray float array.
 * @return the ray in world coordinates
 */
Ray* Camera::makeWorldspaceRay(int i, int j, std::vector<float>* samples) {
  float s1 = samples->at(0);
  float s2 = samples->at(1);

  float u_ij = left + (right - left) * (i + s1) / width;
  float v_ij = bottom + (top - bottom) * (j + s2) / height;
  float w_ij = -1.0;

  Vector4f* v = new Vector4f(u_ij, v_ij, w_ij, 0);
  Vector4f* p_uvw = matrix->mult(v);
  delete v;
  Ray* ray = new Ray(new Vector3f(eye), new Vector3f(p_uvw), i, j);

  delete p_uvw;

  return ray;
}
