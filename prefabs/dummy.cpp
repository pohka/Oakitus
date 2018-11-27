#include "dummy.h"
#include <oak.h>

using namespace game;
using namespace oak;

Dummy::Dummy()
{
  Sprite* sprite = new Sprite("dummy.png", 0, 0, 32, 40, 32.0f, 40.0f, NULL);
  addComponent(*sprite);


}

Dummy::~Dummy()
{

}