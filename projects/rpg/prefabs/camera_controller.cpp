#include "camera_controller.h"
#include <oak/core/camera.h>

using namespace game::prefab;
using namespace oak;

CameraController::CameraController()
{
  hasTarget = false;
}

CameraController::~CameraController()
{
  
}

void CameraController::followTarget(uint entityID)
{
  hasTarget = true;
  targetEntityID = entityID;
}

void CameraController::onLateUpdate()
{
  if (hasTarget)
  {
    Entity* target = Entity::findEntityByID(targetEntityID);

    if (target != nullptr)
    {
      Camera::position.x = target->position.x;
      Camera::position.y = target->position.y;
    }
  }
}