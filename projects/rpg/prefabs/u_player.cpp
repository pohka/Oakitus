#include "u_player.h"
#include <oak/oak.h>
#include "../abilitys/abil_shoot.h"
#include "../abilitys/abil_sword_attack.h"
#include <oak/components/sprite_animation.h>
#include <oak/components/animator.h>
#include <oak/components/rigid_body_2d.h>
#include "../items/item_test.h"

using namespace game::prefab;
using namespace oak;
using namespace game;

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

  addAbility(new abil_Shoot());
  addAbility(new abil_SwordAttack());
  //addCollision(new CollisionRect(-20.0f, -10.0f, 40.0f, 60.0f));
  addCollision(new CollisionCircle(20.0f, 0.0f, 00.0f));
  addRigidBody(new RigidBody2D(false));
  faction = FACTION_PLAYER;
  setMoveSpeed(200);
  this->rigidBody->mass = 10.0f;
  //setHealthRegen(2.0f);
  //setManaRegen(0.0f);
}

UPlayer::~UPlayer()
{

}

//void UPlayer::onCreate() 
//{
//  Unit::onCreate();
//  //testing item
//  inventory.addItem(new ItemTest());
//  inventory.addItem(new ItemTest());
//}