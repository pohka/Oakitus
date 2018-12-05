#include <oak_setup.h>
#include "scenes/main_scene.h"
#include <core/player_resource.h>
#include "player.h"
#include "events/e_damage.h"
#include <event/event_manager.h>

using namespace oak;
using namespace game;


int main()
{
  Oakitus::init();
  return 0;
}


void Oakitus::load()
{
  BaseEvent* damageEvent = new EDamage(EVENT_ON_DAMAGE_TAKEN);
  EventManager::addEvent(damageEvent);

  BasePlayer* player1 = new Player();
  PlayerResource::addPlayer(*player1);

  Scene* mainScene = new MainScene();
  Scene::loadFirstScene(*mainScene);
}

