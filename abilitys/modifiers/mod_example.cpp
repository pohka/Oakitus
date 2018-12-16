#include "mod_example.h"
#include <debug.h>

using namespace game;

mod_Example::mod_Example() : Modifier(MODIFIER_EXAMPLE)
{
  isPassive = true;
  setProp(MODIFIER_PROP_NORMAL_DAMAGE, 10);
  setProp(MODIFIER_PROP_RESIST_NORMAL, 50);
}

void mod_Example::onCreated()
{
  LOG << "test modifier created";
}