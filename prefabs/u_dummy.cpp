#include "u_dummy.h"
#include <oak.h>

using namespace game::prefab;
using namespace oak;

UDummy::UDummy()
{
  Sprite* sprite = new Sprite("dummy.png", 0, 0, 32, 40, 32.0f, 40.0f, NULL);
  addComponent(sprite);
  addComponent(new CollisionRect(0.0f, 0.0f, 32.0f, 40.0f));

  this->name = "dummy";
}

UDummy::~UDummy()
{

}