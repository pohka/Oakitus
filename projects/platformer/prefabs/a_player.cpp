#include "a_player.h"
#include <oak/oak.h>
#include <oak/debug.h>
#include "../scripts/ground_check.h"

using namespace plat;
using namespace oak;

APlayer::APlayer() : Unit()
{
  isPlayer = true;
  collisionLayer = COLLISION_LAYER_PLAYER;
  maxJumpCount = 2;
  name = "actor_player";
  addComponent(new Sprite("face.png", width, height));
  addCollision(new CollisionRect(0.0f, 0.0f, width, height));
  addRigidBody(new RigidBody2D(false));
  addComponent(new GroundCheck());
}


void APlayer::onGroundTouch()
{
  Unit::onGroundTouch();
}