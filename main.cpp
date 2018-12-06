#include <oak_setup.h>
#include "scenes/main_scene.h"
#include <core/player_resource.h>
#include "player.h"
#include "events/e_damage.h"
#include "events/e_death.h"

using namespace oak;
using namespace game;


int main()
{
  Oakitus::init();
  return 0;
}


void Oakitus::load()
{
  Event* damageEvent = new EDamage(EVENT_ON_DAMAGE_TAKEN);
  EventManager::addEvent(damageEvent);
  //Event* deathEvent = new EDeath();
  Event* deathEvent = new EGeneric<DeathListener,DeathData>(EVENT_ON_DEATH, game::deathonFire);
  EventManager::addEvent(deathEvent);

  BasePlayer* player1 = new Player();
  PlayerResource::addPlayer(*player1);

  Scene* mainScene = new MainScene();
  Scene::loadFirstScene(*mainScene);
}

