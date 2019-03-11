#include "triangle.h"

#ifndef MESH_TRIANGLE_H
#define MESH_TRIANGLE_H

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
  MeshTriangle(int, Material*, const Vector3f&, const Vector3f&, const Vector3f&, const Vector3f&,
               const Vector3f&, const Vector3f&);

  void log() const {
    std::cout << "face-index: " << faceId << std::endl;
    std::cout << "vertices: " << std::endl;
    a.log();
    b.log();
    c.log();
    std::cout << "normals: " << std::endl;
    na.log();
    nb.log();
    nc.log();
  }
};

#endif
