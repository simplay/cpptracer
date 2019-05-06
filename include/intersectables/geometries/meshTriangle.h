#ifndef MESH_TRIANGLE_H
#define MESH_TRIANGLE_H

#include "triangle.h"

// Construct a plane given its normal and distance to the origin Note that the
// distance is along the direction that the normal points (meaning that the
// sign of distance matters)
class MeshTriangle : public Triangle {
 protected:
  // vertex normals
  const Vector3f na;
  const Vector3f nb;
  const Vector3f nc;

  Vector3f* computeNormal(float alpha, float beta) const;

 public:
  MeshTriangle(const int, Material*, const Vector3f&, const Vector3f&, const Vector3f&,
               const Vector3f&, const Vector3f&, const Vector3f&);

  const Vector3f& getNormalA() const { return na; }

  const Vector3f& getNormalB() const { return nb; }

  const Vector3f& getNormalC() const { return nc; }
};
#endif
