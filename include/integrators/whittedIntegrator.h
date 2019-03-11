#include "../ray.h"
#include "../scenes/scene.h"
#include "../spectrum.h"
#include "integrator.h"

#ifndef WHITTED_INTEGRATOR_H
#define WHITTED_INTEGRATOR_H
class WhittedIntegrator : public Integrator {
 private:
  Scene* scene;

  // Check whether hitPosition receives light
  //
  // @param hitPosition viewer ray hit (closest)
  // @param L light direction vector
  // @param t parameter of ray equation p_uvw(t) = 0 + t(s_uvw-0)
  // @return is light source occluded by object at hitPostion?
  bool isOccluded(Vector3f* hitPosition, Vector3f* lightDir, float eps);

  // Compute BRDF contribution for a given source at closest intersection point.
  //
  // @param lightSource current point light source.
  // @param hitRecord closest intersection primary ray with scene.
  // @param t parameter of ray equation p_uvw(t) = 0 + t(s_uvw-0).
  // @return returns current spectrum of light source at intersaction point.
  Spectrum* contributionOf(PointLight* lightSource, HitRecord* hitRecord);

 public:
  WhittedIntegrator(Scene*);
  Spectrum* integrate(Ray*);
};
#endif
