#include "hitRecord.h"

HitRecord::~HitRecord() {
  delete position;
  delete normal;
  delete tangent;
  delete wIn;
}

HitRecord::HitRecord()
    : t(0),
      position(new Vector3f()),
      normal(new Vector3f()),
      tangent(new Vector3f()),
      wIn(new Vector3f()) {
  isNull = true;
}

HitRecord::HitRecord(HitRecord* hitRecord)
    : t(hitRecord->t),
      position(new Vector3f(*hitRecord->position)),
      normal(new Vector3f(*hitRecord->normal)),
      tangent(new Vector3f(*hitRecord->tangent)),
      wIn(new Vector3f(*hitRecord->wIn)),
      material(hitRecord->material),
      i(hitRecord->i),
      j(hitRecord->j) {
  this->isNull = !hitRecord->isValid();
}

HitRecord::HitRecord(Vector3f* position, Material* material)
    : t(0),
      position(position),
      normal(new Vector3f()),
      tangent(new Vector3f()),
      wIn(new Vector3f()),
      material(material){};

HitRecord::HitRecord(float t, Vector3f* position, Vector3f* normal, Vector3f* tangent,
                     Vector3f* wIn, Material* material, const Intersectable* intersectable)
    : t(t),
      position(position),
      normal(normal),
      tangent(tangent),
      wIn(wIn),
      material(material),
      intersectable(intersectable) {}

HitRecord::HitRecord(float t, Vector3f* position, Vector3f* normal, Vector3f* tangent,
                     Vector3f* wIn, Material* material, const Intersectable* intersectable, int i,
                     int j)
    : t(t),
      position(position),
      normal(normal),
      tangent(tangent),
      wIn(wIn),
      material(material),
      intersectable(intersectable),
      i(i),
      j(j) {}

bool HitRecord::isValid() { return !isNull; }

HitRecord* HitRecord::transform(Matrix4f* T, Matrix4f* invTranposedT) {
  // transform back
  Vector4f backHitPos(*position, 1);
  auto hitPos = T->mult(&backHitPos);
  auto hit3fPos = hitPos->toVector3f();
  delete hitPos;

  Vector4f backHitNormal(*normal, 0);
  auto hitNormal = invTranposedT->mult(&backHitNormal);
  auto hit3fNormal = hitNormal->toVector3f();
  hit3fNormal->normalize();
  delete hitNormal;

  Vector3f* hit3fTangent = NULL;
  if (tangent) {
    Vector4f backHitTangent(*tangent, 0);
    auto hitTangent = invTranposedT->mult(&backHitTangent);
    hit3fTangent = hitTangent->toVector3f();
    hit3fTangent->normalize();
    delete hitTangent;
  }

  Vector4f backWIn(*wIn, 0);
  auto hitWIn = T->mult(&backWIn);
  auto hit3fWIn = hitWIn->toVector3f();
  hit3fWIn->normalize();

  HitRecord* finalHit = new HitRecord(t, hit3fPos, hit3fNormal, hit3fTangent, hit3fWIn, material,
                                      intersectable, 0, 0);

  return finalHit;
}
