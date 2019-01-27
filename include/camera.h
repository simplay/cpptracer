#include <vector>
#include "math/matrix4f.h"
#include "math/point3f.h"
#include "ray.h"

#ifndef CAMERA_H
#define CAMERA_H

// We define our camera by:
//  + the origin of the camera's eye (eye)
//  + a position in the scene at which the camera is looking at (lookAt) and a
//    vector
//  + that defines the relative upwards direction (up).
// An orthonormal basis M can be constructed by computing
//  w = (eye - lookAt) / norm(eye - lookAt)
//  u = cross_product(up, w) / norm(cross_product(up, w))
//  v = cross_product(w, u)
//  e = eye
//
// and setting M = [u, v, w, e]
//
//           v
//           |                fov / 2       . top
//          |                           .   |
//         |                        .       |
//   w ----e       =>            e----------| Image Plane
//        /                         .  w=-1 |
//       /                              .   |
//      u                                   . bottom
//
//  Camera coordinate System
//
// This matrix can be used to transforms a point in camera coordinates into
// world coordiantes, i.e.  p_xyz = M*p_uvw
//
// The viewing frustum defines the 3d volume that is projected within image
// boundaries and is defined by the vertical field-of-view and the aspect
// ratio.
class Camera {
  Matrix4f* matrix;

  // origin of camera's viewing direction
  Point3f* eye;

  // the point in the scene we are looking at
  Point3f* lookAt;

  // reference vector that define the upwards direction. Notice, that according
  // to our coordinate-system, upwards means having a positive y value.
  Point3f* up;

  // vertical field of view, an angle
  float fov;

  // fraction between width and height of the image.
  float aspectRatio;

  float width;
  float height;

  // top = -bottom = tan(fov / 2) (basic trigonometry fact - see figure above)
  double top;
  double bottom;

  // right = -left = aspectRatio * top
  double right;
  double left;

  public:

  Camera(Point3f* eye, Point3f* lookAt, Point3f* up, float fov, float aspectRatio, float width, float height);

  // used to transform a point in camera coordinates to world coordinates
  Matrix4f* transformation();

  // Creates primary rays
  Ray* makeWorldspaceRay(int i, int j, std::vector<float>);
};

#endif
