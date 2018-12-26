#include <oak/oak_setup.h>
#include "projects/rpg/scenes/main_scene.h"
#include <oak/core/player_resource.h>
#include "projects/rpg/player.h"
#include "projects/rpg/events/e_damage_taken.h"
#include "projects/rpg/strings_def.h"
#include <oak/ui/ui.h>
#include <oak/meta/meta_loader.h>

using namespace oak;
using namespace game;


int main()
{
  uint windowW = 1066;
  uint windowH = 600;

  uint viewportW = 736;
  uint viewportH = 414;

  MetaLoader::load();

  Oakitus::init(viewportW, viewportH, windowW, windowH, false);
  return 0;
}


void Oakitus::load()
{
  //load localized strings
  ion::Localization::addString(STRING_HEALTH, "health:");
  ion::Localization::addString(STRING_MANA, "mana:");

  IEvent* damageEvent = new DamageTakenEvent(EVENT_ON_DAMAGE_TAKEN, game::onDamageTakenFire);
  EventManager::addEvent(damageEvent);
  IEvent* deathEvent = new DeathEvent(EVENT_ON_DEATH, game::onDeathFire);
  EventManager::addEvent(deathEvent);

  BasePlayer* player1 = new Player();
  PlayerResource::addPlayer(*player1);

  Scene* mainScene = new MainScene();
  Scene::loadFirstScene(*mainScene);
}


