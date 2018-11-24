#ifndef POINT3_H
#define POINT3_H

/**
 * Float valued point with 3 coordinates.
 */
class Point3f {
    float _x, _y, _z;

	public:

  Point3f();
  Point3f(float, float, float);

  float x();
  float y();
  float z();

  /**
   * @return dot product of this point's coordinates.
   */
  float dot();
};

#endif