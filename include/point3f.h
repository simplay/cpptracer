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
  Point3f(Point3f*);

  float x();
  float y();
  float z();

  // scale components of this point equally.
  void scale(float factor);

  /**
   * @return l2-dot product of this point's coordinates.
   */
  float dot();

  // Make length of this vector equal 1 (in l2 norm's sense) but preserve its
  // direction.
  void normalize();
};

#endif
