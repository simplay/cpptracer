#include "../hitRecord.h"
#include "../math/vector3f.h"
#include "../shadingSample.h"
#include "../spectrum.h"

#ifndef IMATERIAL_H
#define IMATERIAL_H

/**
 * Materials implement functionality for shading surfaces using their BRDFs.
 * Light sources are implemented using materials that return an emission term.
 */
class Material {
 public:
  /**
   * Evaluate BRDF for pair of incoming and outgoing directions. This method
   * is typically called by an integrator when the integrator obtained the
   * incident direction by sampling a point on a light source.
   *
   * @param hitRecord Information about hit point
   * @param wOut Outgoing direction, normalized and pointing away from the
   *  surface
   * @param wIn Incoming direction, normalized and pointing away from the
   *  surface
   * @return BRDF value
   */
  virtual Spectrum* evaluateBrdf(HitRecord* hitRecord, Vector3f* wOut, Vector3f* wIn) = 0;

  /**
   * Evaluate emission for outgoing direction. This method is typically
   * called by an integrator when the integrator obtained the outgoing
   * direction of the emission by sampling a point on a light source.
   *
   * @param hitRecord Information about hit point on light source
   * @param wOut Outgoing direction, normalized and pointing away from the
   *  surface
   * @return emission value
   */
  virtual Spectrum* evaluateEmission(HitRecord* hitRecord, Vector3f* wOut) = 0;

  /**
   * Return whether material has perfect specular reflection.
   */
  virtual bool hasSpecularReflection() = 0;

  /**
   * Return whether the material has perfect specular refraction.
   */
  virtual bool hasSpecularRefraction() = 0;

  /**
   * Indicate whether the material casts shadows or not.
   */
  virtual bool castsShadows() = 0;

  /**
   * Evaluate specular reflection. This method is typically called by a recursive
   * ray tracer to follow the path of specular reflection.
   */
  virtual ShadingSample* evaluateSpecularReflection(HitRecord* hitRecord) = 0;

  /**
   * Evaluate specular refraction. This method is typically called by a
   * recursive ray tracer to follow the path of specular refraction.
   */
  virtual ShadingSample* evaluateSpecularRefraction(HitRecord* hitRecord) = 0;
};
#endif
