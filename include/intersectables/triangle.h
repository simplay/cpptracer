#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../hitRecord.h"
#include "../math/vector3f.h"
#include "../ray.h"
#include "boundingBox.h"
#include "intersectable.h"

class Material;

// Construct a plane given its normal and distance to the origin Note that the
// distance is along the direction that the normal points (meaning that the
// sign of distance matters)
class Triangle : public Intersectable {
 private:
  BoundingBox computeAABB(const Vector3f& a, const Vector3f& b, const Vector3f& c) {
    auto minX = a.x;
    auto minY = a.y;
    auto minZ = a.z;

    if (b.x < minX) {
      minX = b.x;
    }

    if (b.y < minY) {
      minY = b.y;
    }

    if (b.z < minZ) {
      minZ = b.z;
    }

    if (c.x < minX) {
      minX = c.x;
    }

    if (c.y < minY) {
      minY = c.y;
    }

    if (c.z < minZ) {
      minZ = c.z;
    }

    auto maxX = a.x;
    auto maxY = a.y;
    auto maxZ = a.z;

    if (b.x > maxX) {
      maxX = b.x;
    }

    if (b.y > maxY) {
      maxY = b.y;
    }

    if (b.z > maxZ) {
      maxZ = b.z;
    }

    if (c.x > maxX) {
      maxX = c.x;
    }

    if (c.y > maxY) {
      maxY = c.y;
    }

    if (c.z > maxZ) {
      maxZ = c.z;
    }

    auto bottomLeft = Vector3f(minX, minY, minZ);
    auto topRight = Vector3f(maxX, maxY, maxZ);

    return BoundingBox(bottomLeft, topRight);
  }

 protected:
  const int faceId;
  Material* material;

  // normal of the plane
  const Vector3f a;
  const Vector3f b;
  const Vector3f c;
  const BoundingBox aabb;

  virtual Vector3f* computeNormal(float alpha, float beta) const;

 public:
  Triangle(const int, Material*, const Vector3f&, const Vector3f&, const Vector3f&);

  // plane-ray intersection ray: p(t) = orig + t * dir
  //
  // Implicit plane:
  // f(p) = dot(n, (p - a)) intersection:
  // f(p(t)) = 0. Solve for t.  Plug t_i into
  // p(t_i) will give intersection point
  HitRecord* intersect(const Ray& ray) const;

  int getFaceId() const { return faceId; }

  const Vector3f& getVertexA() const { return a; }

  const Vector3f& getVertexB() const { return b; }

  const Vector3f& getVertexC() const { return c; }

  BoundingBox getBoundingBox() const { return aabb; }
};
#endif
