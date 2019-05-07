#ifndef CSG_SOLID_H
#define CSG_SOLID_H

#include <limits>
#include "hitRecord.h"
#include "intersectables/accelerator/boundingBox.h"
#include "intersectables/intersectable.h"
#include "ray.h"

/**
 * A CsgSolid is an Intersectable that not just allows to get the closest hit
 * point - when intersected by a ray - but also allows to query the start-and
 * endpoint of an intersection with a ray (i.e. the so called intersection
 * interval).
 */
class CsgSolid : public Intersectable {
 public:
  enum BoundaryType { START = 0, END = 1 };
  enum BelongsTo { LEFT = 0, RIGHT = 1 };

  /**
   * Boundary of an intersection interval.
   */
  struct IntervalBoundary {
    // t value of intersection
    float t;
    // Type of boundary of intersection interval (start or end)
    BoundaryType type;

    // The hit record of the intersection
    HitRecord* hitRecord;

    BelongsTo belongsTo;

    bool operator>(const IntervalBoundary& other) { return t > other.t; };
  };

  BoundingBox aabb = BoundingBox(Vector3f(std::numeric_limits<float>::min()),
                                 Vector3f(std::numeric_limits<float>::max()));

  virtual HitRecord* intersect(const Ray& ray) const;
  virtual const BoundingBox& getBoundingBox() const;

	/**
   * Compute the boundaries of the intersection intervals of this CSG solid
   * with a ray.
	 *
	 * @param r the ray that intersects the CSG solid
	 * @return boundaries of intersection intervals
	 */
	virtual std::vector<IntervalBoundary>& getIntervalBoundaries(Ray r) const = 0;
};
#endif
