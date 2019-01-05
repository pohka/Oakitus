#include "a_player.h"
#include <oak/oak.h>
#include <oak/debug.h>

using namespace plat;
using namespace oak;

APlayer::APlayer() : Actor()
{
  addComponent(new Sprite("face.png", 64.0f, 64.0f));
  addCollision(new CollisionRect(0.0f, 0.0f, 64.0f, 64.0f));
  addRigidBody(new RigidBody2D(false));
}
