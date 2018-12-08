#include <oak_setup.h>
#include "scenes/main_scene.h"
#include <core/player_resource.h>
#include "player.h"
#include "events/e_damage_taken.h"

using namespace oak;
using namespace game;


int main()
{
  uint windowW = 1920;
  uint windowH = 1080;

  uint virwportW = 1920;
  uint viewportH = 1080;

  Oakitus::init(736, 414, windowW, windowH, true);
  return 0;
}


void Oakitus::load()
{
  IEvent* damageEvent = new DamageTakenEvent(EVENT_ON_DAMAGE_TAKEN, game::onDamageTakenFire);
  EventManager::addEvent(damageEvent);
  //Event* deathEvent = new EDeath();
  IEvent* deathEvent = new DeathEvent(EVENT_ON_DEATH, game::onDeathFire);
  EventManager::addEvent(deathEvent);

  BasePlayer* player1 = new Player();
  PlayerResource::addPlayer(*player1);

  Scene* mainScene = new MainScene();
  Scene::loadFirstScene(*mainScene);
}


