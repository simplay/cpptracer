#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include "math/matrix4f.h"
#include "math/vector3f.h"
#include "ray.h"

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
 private:
  // used to transform a point in camera coordinates to world coordinates
  Matrix4f* matrix;

  // origin of camera's viewing direction
  Vector3f* eye;

  float width;
  float height;

  // top = -bottom = tan(fov / 2) (basic trigonometry fact - see figure above)
  double top;
  double bottom;

  // right = -left = aspectRatio * top
  double right;
  double left;

 public:

  /**
   * @param fov vertical field of view, an angle
   * @param lookAt the point in the scene we are looking at.
   * @param up reference vector that define the upwards direction.
   *  Notice, that according to our coordinate-system, upwards means
   *  having a positive y value.
   * @param aspectRatio fraction between width and height of the image.
   **/
  Camera(Vector3f* eye, Vector3f* lookAt, Vector3f* up, float fov, float aspectRatio, float width,
         float height);

  Matrix4f* transformation();

  // Creates primary rays
  Ray makeWorldspaceRay(int i, int j, std::vector<float>*) const;
};
#endif
