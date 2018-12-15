#include "modifier_test.h"
#include <debug.h>

using namespace game;

ModifierTest::ModifierTest()
{
  duration = 3.0f;
  addProperty(MODIFIER_NORMAL_DAMAGE, 10);
}

void ModifierTest::onCreated()
{
  LOG << "test modifier created";
}