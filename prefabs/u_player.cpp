#include "u_player.h"
#include <oak.h>
#include "../abilitys/shoot.h"
#include "../oak/components/sprite_animation.h"
#include "../oak/components/animator.h"

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
      192, 192, 
      100, 100, 
      0.04f, 
      "default", 
      14, 
      0
    )
  );

  animator->addAnim(
    ANIM_TYPE_RUN,
    new SpriteAnimation(
      "anim_test2.png",
      192, 192,
      100, 100,
      0.04f,
      "default",
      12,
      2
    )
  );

  animator->addAnim(
    ANIM_TYPE_ATTACK,
    new SpriteAnimation(
      "anim_test2.png",
      384, 192,
      200, 100,
      0.04f,
      "default",
      14,
      4
    )
  );

  animator->setAnim(ANIM_TYPE_IDLE);
  addAnimator(animator);

  //addComponent(
  //  new SpriteAnimation(
  //   // "anim_test2.png", 192, 192, 100, 100, 0.04f, "default", 14, 0)
  //    //"anim_test2.png", 192, 192, 100, 100, 0.04f, "default", 12, 2)
  //    "anim_test2.png", 384, 192, 200, 100, 0.04f, "default", 14, 4)
  //);
  addAbility(new Shoot());
  addCollision(new CollisionRect(10.0f, -10.0f, 40.0f, 60.0f));
  faction = FACTION_PLAYER;
}

UPlayer::~UPlayer()
{

}