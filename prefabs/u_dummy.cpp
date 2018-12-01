#include "u_dummy.h"
#include <oak.h>

using namespace game::prefab;
using namespace oak;

UDummy::UDummy()
{
  Sprite* sprite = new Sprite("dummy.png", 0, 0, 32, 40, 32.0f, 40.0f, "default");
  addComponent(sprite);
 // addCollision(new CollisionRect(0.0f, 0.0f, 32.0f, 40.0f));
  addCollision(new CollisionCircle(20.0f, 0.0f, 0.0f));
  faction = Faction::ENEMY;
  this->name = "dummy";
}

UDummy::~UDummy()
{

}