#include "camera_follow.h"
#include "../reflect.h"

using namespace plat;
using namespace oak;

CameraFollow::CameraFollow() : Component(REFLECT_CAMERA_FOLLOW, TICK_GROUP_AFTER_PHYSICS, TICK_TYPE_TICKABLE, false)
{

}

void CameraFollow::setTarget(Entity* target)
{
  targetID = target->getID();
}

void CameraFollow::onTick()
{
  Entity* target = EntityManager::findEntityByID(targetID);
  if (target != nullptr)
  {
    Camera::position.x = target->transform->position().x;
    Camera::position.y = target->transform->position().y;
  }
}