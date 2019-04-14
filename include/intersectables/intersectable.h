#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

#include "../hitRecord.h"
#include "../ray.h"

class BoundingBox;

class Intersectable {
 public:
  /**
   * Implement ray-surface intersection in this method. Implementations of this
   * method need to make and return a {@link HitRecord} correctly, following
   * the conventions assumed for {@link HitRecord}.
   *
   * @param ray the ray used for intersection testing
   * @return a hit record, should return an invalid hit record if there is no
   *   intersection
   */
  virtual HitRecord* intersect(const Ray& ray) const = 0;

  virtual const BoundingBox& getBoundingBox() const = 0;
};
#endif
