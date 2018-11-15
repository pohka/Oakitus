#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

namespace oak
{
  class Ray
  {
    glm::vec3 direction;
    glm::vec3 origin;

    public:
      Ray(glm::vec3 origin, glm::vec3 direction);
      ~Ray();
      glm::vec3 planeIntersectPoint(glm::vec3 planeNormal, glm::vec3 planePoint);

  };
}

#endif
