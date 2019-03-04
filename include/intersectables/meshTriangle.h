#include "triangle.h"

#ifndef MESH_TRIANGLE_H
#define MESH_TRIANGLE_H

// Construct a plane given its normal and distance to the origin Note that the
// distance is along the direction that the normal points (meaning that the
// sign of distance matters)
class MeshTriangle : public Triangle {
  public:
    // vertex normals
    Point3f* na;
    Point3f* nb;
    Point3f* nc;

    Point3f* computeNormal(float alpha, float beta) const;
    MeshTriangle(int, Material*, Point3f*, Point3f*, Point3f*, Point3f*, Point3f*, Point3f*);

    void log() {
      std::cout << "face-index: " << faceId << std::endl;
      std::cout << "vertices: " <<  std::endl;
      a->log();
      b->log();
      c->log();
      std::cout << "normals: " << std::endl;
      na->log();
      nb->log();
      nc->log();
    }
};

#endif
