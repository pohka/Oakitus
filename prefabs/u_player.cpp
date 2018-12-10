#include "u_player.h"
#include <oak.h>
#include "../abilitys/shoot.h"
#include "../abilitys/sword_attack.h"
#include "../oak/components/sprite_animation.h"
#include "../oak/components/animator.h"
#include "../oak/components/rigid_body_2d.h"

using namespace game::prefab;
using namespace oak;
using namespace game::ability;

UPlayer::UPlayer()
{
  name = "u_player";
  //Sprite* sprite = new Sprite("player.png", 0, 0, 32, 40, 32.0f, 40.0f, "default");
  //addComponent(sprite);
  Animator* animator = new Animator(
    ANIM_TYPE_IDLE,
    new SpriteAnimation(
      "anim_test2.png", 
      ANIM_PRIORITY_BASE,
      192, 192, 
      100, 100, 
      0.04f, 
      "default", 
      14, 
      0,
      true
    )
  );

  animator->addAnim(
    ANIM_TYPE_RUN,
    new SpriteAnimation(
      "anim_test2.png",
      ANIM_PRIORITY_BASE,
      192, 192,
      100, 100,
      0.04f,
      "default",
      12,
      2,
      true
    )
  );

  animator->addAnim(
    ANIM_TYPE_ABILITY_1,
    new SpriteAnimation(
      "anim_test2.png",
      ANIM_PRIORITY_ABILITY,
      384, 192,
      200, 100,
      0.04f,
      "default",
      14,
      4,
      false
    )
  );

  animator->addAnim(
    ANIM_TYPE_ABILITY_2,
    new SpriteAnimation(
      "anim_test2.png",
      ANIM_PRIORITY_ABILITY,
      384, 192,
      200, 100,
      0.04f,
      "default",
      14,
      4,
      false
    )
  );

 
  addAnimator(animator);

  addAbility(new Shoot());
  addAbility(new SwordAttack());
  addCollision(new CollisionRect(0.0f, -10.0f, 40.0f, 60.0f));
  addRigidBody(new RigidBody2D(false));
  faction = FACTION_PLAYER;
}

UPlayer::~UPlayer()
{

}