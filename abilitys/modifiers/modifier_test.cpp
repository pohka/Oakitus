#include "modifier_test.h"
#include <debug.h>

using namespace game;

ModifierTest::ModifierTest()
{
  isPassive = true;
  setProp(MODIFIER_PROP_NORMAL_DAMAGE, 10);
  setProp(MODIFIER_PROP_RESIST_NORMAL, 50);
}

void ModifierTest::onCreated()
{
  LOG << "test modifier created";
}