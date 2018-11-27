#include "u_dummy.h"
#include <oak.h>

using namespace game::prefab;
using namespace oak;

UDummy::UDummy()
{
  Sprite* sprite = new Sprite("dummy.png", 0, 0, 32, 40, 32.0f, 40.0f, NULL);
  addComponent(*sprite);


}

UDummy::~UDummy()
{

}