#ifndef BASE_RIGID_BODY_H
#define BASE_RIGID_BODY_H

#include "../core/component.h"
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
      BaseRigidBody(bool isStatic);

      void onStart() override;
      void onLateUpdate() override;
  };
}

#endif