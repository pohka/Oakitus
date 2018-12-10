#include "base_rigid_body.h"
#include "../core/entity.h"
#include <debug.h>


using namespace oak;

BaseRigidBody::BaseRigidBody(bool isStatic)
{
  this->isStatic = isStatic;
  lastPos = glm::vec3(0.0f, 0.0f, 0.0f);
  velocity = glm::vec3(0.0f, 0.0f, 0.0f);
  nextPos = glm::vec3(0.0f, 0.0f, 0.0f);
  desiredNextPos = glm::vec3(0.0f, 0.0f, 0.0f);
}

void BaseRigidBody::onStart()
{
  lastPos = entity->position;
}

//void BaseRigidBody::onResolveFinsihed()
//{
//  desiredNextPos = entity->position;
//  nextPos = desiredNextPos;
//  velocity = desiredNextPos - lastPos;
//}