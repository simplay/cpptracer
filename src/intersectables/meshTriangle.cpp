#include "meshTriangle.h"
#include "../math/point3f.h"

MeshTriangle::MeshTriangle(
  int faceId,
  Material* material,
  Point3f* a,
  Point3f* b,
  Point3f* c,
  Point3f* na,
  Point3f* nb,
  Point3f* nc
)
  : Triangle(faceId, material, a, b, c),
    na(na), nb(nb), nc(nc) {}


// weighted average of provided vertex normals
Point3f* MeshTriangle::computeNormal(float alpha, float beta) {
  auto alphabeta = alpha + beta;
  Point3f nx(na);
  nx.scale(1.0 - alphabeta);

  Point3f ny(nb);
  ny.scale(alpha);

  Point3f nz(nc);
  nz.scale(beta);

  nx.add(&ny);
  nx.add(&nz);

  auto n = new Point3f(&nx);
  n->normalize();
  return n;
}
