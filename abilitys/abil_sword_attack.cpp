#include "abil_sword_attack.h"
#include <debug.h>

using namespace game;

abil_SwordAttack::abil_SwordAttack()
{
  targetType = TARGET_TYPE_NO_TARGET;
  preCastTime = 0.0f;
  castTime = 0.5f;
}

abil_SwordAttack::~abil_SwordAttack()
{

}


void abil_SwordAttack::onCast()
{
  LOG << "onCast sword attack";
  caster->setAnimation(ANIM_TYPE_ABILITY_2);
}

void abil_SwordAttack::onAbilityStart()
{
  caster->heal(5);
}

void abil_SwordAttack::onAbilityEnd()
{

}