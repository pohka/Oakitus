#include "u_dummy.h"
#include <oak.h>
#include <debug.h>
#include <event/event_manager.h>
#include "../events/e_damage.h"

using namespace game::prefab;
using namespace oak;

UDummy::UDummy()
{
  //Sprite* sprite = new Sprite("dummy.png", 0, 0, 32, 40, 32.0f, 40.0f, "default");
 // addComponent(sprite);
 // addCollision(new CollisionRect(0.0f, 0.0f, 32.0f, 40.0f));
  addCollision(new CollisionCircle(20.0f, 0.0f, 0.0f));
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
  BaseEvent* e = EventManager::getEventByID(EVENT_ON_DAMAGE_TAKEN);
  EDamage* damageEvent = static_cast<EDamage*>(e);// .addListener(this);
  damageEvent->addListener(this);
}

UDummy::~UDummy()
{

}
void UDummy::onDamageTaken(int amount)
{
  LOG << "onDamageTaken() " << amount;
}