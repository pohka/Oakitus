#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>
using namespace glm;


class Ray
{
  vec3 direction;
  vec3 origin;

  public:
    Ray(vec3 origin, vec3 direction);
    ~Ray();
    vec3 planeIntersectPoint(vec3 planeNormal, vec3 planePoint);

};

#endif
