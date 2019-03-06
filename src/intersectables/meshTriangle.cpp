#include "meshTriangle.h"
#include "../math/vector3f.h"

MeshTriangle::MeshTriangle(
  int faceId,
  Material* material,
  Vector3f* a,
  Vector3f* b,
  Vector3f* c,
  Vector3f* na,
  Vector3f* nb,
  Vector3f* nc
)
  : Triangle(faceId, material, a, b, c),
    na(na), nb(nb), nc(nc) {}


// weighted average of provided vertex normals
Vector3f* MeshTriangle::computeNormal(float alpha, float beta) const {
  auto alphabeta = alpha + beta;
  Vector3f nx(na);
  nx.scale(1.0 - alphabeta);

  Vector3f ny(nb);
  ny.scale(alpha);

  Vector3f nz(nc);
  nz.scale(beta);

  nx.add(&ny);
  nx.add(&nz);

  auto n = new Vector3f(&nx);
  n->normalize();
  return n;
}
