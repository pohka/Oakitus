#include "a_player.h"
#include <oak/oak.h>
#include <oak/debug.h>

using namespace plat;
using namespace oak;

APlayer::APlayer() : Actor()
{
  float w = 34.0f;
  float h = 40.0f;
  addComponent(new Sprite("face.png", w, h));
  addCollision(new CollisionRect(0.0f, 0.0f, w, h));
  addRigidBody(new RigidBody2D(false));

  Entity* ent = new Entity();
  ent->addComponent(new Sprite("face.png", 120.0f, 30.0f));
  this->addChild(ent);

  //Entity* ent2 = new Entity();
  //ent2->name = "thing";
  //ent2->addComponent(new Sprite("face.png", 120.0f, 30.0f));
  //ent2->create(100.0f, -100.0f);


}
