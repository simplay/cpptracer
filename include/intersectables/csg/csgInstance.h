#ifndef CSG_INSTANCE_H
#define CSG_INSTANCE_H

#include "hitRecord.h"
#include "intersectables/accelerator/boundingBox.h"
#include "intersectables/containers/instance.h"
#include "intersectables/csg/csgSolid.h"
#include "math/matrix4f.h"
#include "math/vector3f.h"
#include "ray.h"

class CsgInstance : public CsgSolid, public Instance {
 private:
  CsgSolid* solid;

 public:
  CsgInstance(CsgSolid*);
  CsgInstance(CsgSolid*, Matrix4f*);
  std::vector<CsgSolid::IntervalBoundary> getIntervalBoundaries(const Ray& ray) const;
};
#endif
