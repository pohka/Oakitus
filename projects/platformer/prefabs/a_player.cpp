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

  Entity* ent = new Entity();
  ent->addComponent(new Sprite("face.png", 120.0f, 30.0f));
  this->addChild(ent);

  Entity* ent2 = new Entity();
  ent2->name = "thing";
  ent2->addComponent(new Sprite("face.png", 120.0f, 30.0f));
  ent2->create(100.0f, -100.0f);

}
