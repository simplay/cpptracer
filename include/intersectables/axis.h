#ifndef AXIS_H
#define AXIS_H

#include "../math/vector3f.h"

/**
 * Models a coordinate axis used to split axis aligned bounding boxes
 */
class Axis {
 public:
  enum Label { X = 0, Y = 1, Z = 2 };
  Label static nextLabel(Label other) {
    switch (other) {
      case X:
        return Y;
      case Y:
        return Z;
      case Z:
        return X;
      default:
        return X;
    }
  }

  Vector3f static valueOf(Label axis) {
    switch (axis) {
      case X:
        return Vector3f(1, 0, 0);
      case Y:
        return Vector3f(0, 1, 0);
      case Z:
        return Vector3f(0, 0, 1);
      default:
        return Vector3f(1, 0, 0);
    }
  }
};

#endif
