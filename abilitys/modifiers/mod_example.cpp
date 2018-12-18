#include "mod_example.h"
#include "../unit.h"
#include <debug.h>
#include "../../damage.h"

using namespace game;

mod_Example::mod_Example() : Modifier(MODIFIER_EXAMPLE)
{
  //destroyOnExpire = false;
  duration = 3.0f;
  setProp(MODIFIER_PROP_NORMAL_DAMAGE, 10);
  setProp(MODIFIER_PROP_AMP_NORMAL, 50);
  setProp(MODIFIER_PROP_RESIST_NORMAL, 50);
  setProp(MODIFIER_PROP_HEALTH, 5);
  setProp(MODIFIER_PROP_MANA, 450);
  setProp(MODIFIER_PROP_HEALTH_REGEN, 35);
  setProp(MODIFIER_PROP_MANA_REGEN, 15);
  
  startTicker(1.55f);
}

void mod_Example::onCreated()
{
  LOG << "test modifier created";
}

void mod_Example::onDestroy()
{
  LOG << "modifier destroyed";
}

void mod_Example::onDeath()
{
  LOG << "owner of the modifier died, unitID:" << owner->getID();
}

void mod_Example::onRefresh()
{

}

void mod_Example::onIntervalTick()
{
  LOG << "TICKING";
  DamageData damage;
  damage.amount = 10.0f;
  damage.element = ELEMENT_FIRE;
  damage.casterID = owner->getID();
  damage.victimID = owner->getID();
  Damage::apply(damage);
}