#include "sword_attack.h"
#include <debug.h>

using namespace game;

SwordAttack::SwordAttack()
{
  targetType = TARGET_TYPE_NO_TARGET;
  preCastTime = 0.0f;
  castTime = 0.5f;
}

SwordAttack::~SwordAttack()
{

}


void SwordAttack::onCast()
{
  LOG << "onCast sword attack";
  caster->setAnimation(ANIM_TYPE_ABILITY_2);
}

void SwordAttack::onAbilityStart()
{

}

void SwordAttack::onAbilityEnd()
{

}