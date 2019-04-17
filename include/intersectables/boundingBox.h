#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "../hitRecord.h"
#include "../ray.h"
#include "intersectable.h"
#include "math/vector3f.h"
#include "axis.h"

#include <vector>
#include <array>

/**
 * Axis Aligned Bounding Box (AABB)
 *
 *
 *                           top-right
 *         (min_x, max_y)    (max_x, max_y)
 *               +-----------------+
 *               |                 |
 *               |       AABB      |
 *               |                 |
 *               |                 |
 *               +-----------------+
 *         (min_x, min_y)    (max_x, min_y)
 *         bottom-left
 *
 * A computationally- and memory-efficient way of representing a volume that
 * encloses the surface of intersectable. The edges of the box are parallel to
 * the coordinate axes.
 *
 * It is typically used to check if two objects might be touching / are
 * intersecting.
 *
 * Example
 *  Source: https://stackoverflow.com/questions/22512319/what-is-aabb-collision-detection:
 *  Imagine you are in a 2D, which can be drawn on a sheet of paper. You have
 *  some objects in the world (a ball, a tree, whatever). To make an AABB for one
 *  of the objects, you draw a rectangle around the object, making your lines
 *  parallel to the grid lines on the paper.

 *  If you have the AABB for two objects, you can do some pretty simple math to
 *  see if those AABBs overlap. If they don't overlap, those two objects couldn't
 *  possibly be touching, so it's an easy early-out for your collision algorithm.
 */
class BoundingBox : public Intersectable {
 private:
  const Vector3f bottomLeft;
  const Vector3f topRight;

 public:
  // Builds a bounding box around the convex hull of all vectors
  BoundingBox static buildFromVectors(const std::vector<Vector3f>& vectors);
  BoundingBox& operator=(const BoundingBox& newBB) {
    // This is a hack used to update certain const members whenever we put new
    // members in IntersectableList.
    *(Vector3f*)&bottomLeft = Vector3f(newBB.getBottomLeft());
    *(Vector3f*)&topRight = Vector3f(newBB.getTopRight());
    return *this;
  }

  BoundingBox(const Vector3f& bottomLeft, const Vector3f& topRight);
  HitRecord* intersect(const Ray& ray) const;
  const BoundingBox& getBoundingBox() const;

  const Vector3f& getBottomLeft() const { return bottomLeft; }

  const Vector3f& getTopRight() const { return topRight; }

  BoundingBox transform(Matrix4f& transformation) const;
  void expand(const Intersectable*);

  /**
   * Splits this bounding box into two bounding boxes.
   *
   * @param label The coordinate axis along which the box should be split.
   * @param t position on 1D coordinate axis along we want to split the bounding box.
   * @return An array that contains two bounding boxes.
   */
  std::array<BoundingBox, 2> split(Axis::Label label, float t);

  bool overlaps(const BoundingBox&) const;
};
#endif
