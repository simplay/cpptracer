#include "integrator.h"
#include "../spectrum.h"
#include "../scenes/scene.h"
#include "../ray.h"

#ifndef POINT_LIGHT_INTEGRATOR_H
#define POINT_LIGHT_INTEGRATOR_H
class PointLightIntegrator : public Integrator {
  private:
    Scene* scene;

    // Check whether hitPosition receives light
    //
    // @param hitPosition viewer ray hit (closest)
    // @param L light direction vector
    // @param t parameter of ray equation p_uvw(t) = 0 + t(s_uvw-0)
    // @return is light source occluded by object at hitPostion?
    bool isOccluded(Point3f* hitPosition, Point3f* lightDir, float eps);


    // Compute BRDF contribution for a given source at closest intersection point.
    //
    // @param lightSource current point light source.
    // @param hitRecord closest intersection primary ray with scene.
    // @param t parameter of ray equation p_uvw(t) = 0 + t(s_uvw-0).
    // @return returns current spectrum of light source at intersaction point.
    Spectrum* contributionOf(PointLight* lightSource, HitRecord* hitRecord);

  public:
    PointLightIntegrator(Scene*);
    Spectrum* integrate(Ray*);
};
#endif
