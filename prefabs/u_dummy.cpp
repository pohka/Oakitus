#include "u_dummy.h"
#include <oak.h>
#include <debug.h>
#include "../scripts/ai_test.h"
#include "../abilitys/modifiers/mod_example.h"

using namespace game::prefab;
using namespace oak;

UDummy::UDummy()
{
  //Sprite* sprite = new Sprite("dummy.png", 0, 0, 32, 40, 32.0f, 40.0f, "default");
 // addComponent(sprite);
 // addCollision(new CollisionRect(0.0f, 0.0f, 32.0f, 40.0f));
  addCollision(new CollisionCircle(20.0f, 0.0f, 0.0f));
  addRigidBody(new RigidBody2D(false));
  faction = FACTION_ENEMY;
  this->name = "dummy";

  Animator* animator = new Animator(
    ANIM_TYPE_IDLE,
    new SpriteAnimation(
      "wolf_sheet.png",
      ANIM_PRIORITY_BASE,
      192, 192,
      100, 100,
      0.04f,
      "default",
      12,
      0,
      true
    )
  );
  addAnimator(animator);


  addComponent(new AITest());
}

UDummy::~UDummy()
{

}

void UDummy::onCreate()
{
  Unit::onCreate();
  //ddModifier(getID(), new mod_Example());
}
