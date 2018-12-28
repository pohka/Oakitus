#include "base_rigid_body.h"
#include <oak/core/entity.h>
#include <oak/debug.h>


using namespace oak;

BaseRigidBody::BaseRigidBody(bool isStatic) : Component()
{
  this->isStatic = isStatic;
  lastPos = glm::vec3(0.0f, 0.0f, 0.0f);
  velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  nextPos = glm::vec3(0.0f, 0.0f, 0.0f);
  desiredNextPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void BaseRigidBody::onCreate()
{
  lastPos = entity->position;
}
