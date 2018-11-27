#include "camera_follow.h"

using namespace game;
using namespace oak;

CameraFollow::CameraFollow()
{

}

CameraFollow::~CameraFollow()
{

}



void CameraFollow::init()
{

}

void CameraFollow::onUpdate()
{
  Camera::position.x = entity->position.x;
  Camera::position.y = entity->position.y;
}