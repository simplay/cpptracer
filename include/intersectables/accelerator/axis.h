#ifndef AXIS_H
#define AXIS_H

#include "../../math/vector3f.h"

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

  float static valueOf(Label axis, Vector3f v) {
    switch (axis) {
      case X:
        return v.x;
      case Y:
        return v.y;
      case Z:
        return v.z;
      default:
        return v.x;
    }
  }
};

#endif
