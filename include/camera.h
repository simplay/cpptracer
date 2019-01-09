#include <vector>
#include "matrix4f.h"
#include "point3f.h"
#include "ray.h"

#ifndef CAMERA_H
#define CAMERA_H

// Boxfilter-film
class Camera {
  Matrix4f* matrix;
  Point3f* eye;
  Point3f* lookAt;
  Point3f* up;
  float fov;
  float aspectRatio;
  float width;
  float height;
  double top;
  double bottom;
  double right;
  double left;

  public:

  Camera(Point3f* eye, Point3f* lookAt, Point3f* up, float fov, float aspectRatio, float width, float height);
  Matrix4f* transformation();
  Ray* makeWorldspaceRay(int i, int j, std::vector<float>);
};

#endif
