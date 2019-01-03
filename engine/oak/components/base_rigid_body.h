#ifndef BASE_RIGID_BODY_H
#define BASE_RIGID_BODY_H

#include <oak/ecs/component.h>
#include <glm/glm.hpp>

namespace oak
{
  class BaseRigidBody : public Component
  {
    glm::vec3 lastPos;
    glm::vec3 desiredNextPos;
    glm::vec3 velocity;
    glm::vec3 nextPos;
    

    public:
      friend class Collision;
      bool isStatic;
      float mass = 1.0f;

      BaseRigidBody(bool isStatic);

      void onCreate() override;
  };
}

#endif