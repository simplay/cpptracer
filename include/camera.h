#include "point3f.h"

#ifndef CAMERA_H
#define CAMERA_H

// Boxfilter-film
class Camera {
  Point3f* eye;
  Point3f* lookAt;
  Point3f* up;
  float fov;
  float aspectRatio;
  float width;
  float height;

  public:

  Camera(Point3f* eye, Point3f* lookAt, Point3f* up, float fov, float aspectRatio, float width, float height);
};

#endif
