#include "abil_shoot.h"
#include <debug.h>
#include "../prefabs/projectile_linear.h"
#include "../oak/components/sprite.h"

using namespace game;

abil_Shoot::abil_Shoot()
{
  targetType = TARGET_TYPE_POINT;
  preCastTime = 0.0f;
  castTime = 0.5f;
  manaCost = 1;
}

abil_Shoot::~abil_Shoot()
{
  LOG << "Delocated shoot ability";
}

void abil_Shoot::onCast()
{
  //LOG << "onCast()";
  owner->setAnimation(ANIM_TYPE_ABILITY_1);
}

void abil_Shoot::onAbilityStart()
{
  DamageData damage;
  damage.amount = 20.0f;
  damage.element = ELEMENT_NORMAL;
  damage.casterID = owner->getID();
  damage.victimID = 0;

  prefab::Projectile* proj = new prefab::ProjectileLinear(
    target.point, 
    *owner, 
    getAbilityID(),
    damage,
    150.0f,
    15.0f
  );
  //proj->addComponent(new oak::Sprite("face.png", 30.0f, 30.0f));
  oak::Animator* animator = new oak::Animator(
    1,
    new oak::SpriteAnimation(
      "anim_arrow.png", 
      ANIM_PRIORITY_BASE, 
      32,32, //frame size
      32,32, //display size
      0.04f, 
      "default", 
      6, 
      0, 
      true
    )
  );
  proj->addComponent(animator);

  proj->create(owner->position.x, owner->position.y);
}

void abil_Shoot::onAbilityEnd()
{

}