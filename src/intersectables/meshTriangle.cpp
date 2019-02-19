#include "meshTriangle.h"
#include "../math/point3f.h"

MeshTriangle::MeshTriangle(
  Material* material,
  Point3f* a,
  Point3f* b,
  Point3f* c,
  Point3f* na,
  Point3f* nb,
  Point3f* nc
)
  : Triangle(material, a, b, c),
    na(na), nb(nb), nc(nc) {}


Point3f* MeshTriangle::computeNormal(float alpha, float beta) {
  Point3f nx(na);
  nx.scale(1.0 - alpha - beta);

  Point3f ny(nb);
  ny.scale(alpha);

  Point3f nz(nc);
  nz.scale(beta);

  nx.add(&ny);
  nx.add(&nz);

  return new Point3f(&nx);
}
