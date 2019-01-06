#include "camera.h"
#include "point3f.h"

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
  height(height) {
}
