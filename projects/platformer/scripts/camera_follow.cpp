#include "camera_follow.h"

using namespace plat;
using namespace oak;

CameraFollow::CameraFollow() : Component(TICK_GROUP_AFTER_PHYSICS, TICK_TYPE_TICKABLE, false)
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
    Camera::position.x = target->position.x;
    Camera::position.y = target->position.y;
  }
}