#include <oak/oak_setup.h>
#include <oak/core/player_resource.h>
//#include <oak/ui/ui.h>
#include <oak/debug.h>


void oak::Oakitus::load()
{
  //load localized strings
  //ion::Localization::addString(STRING_HEALTH, "health:");
  //ion::Localization::addString(STRING_MANA, "mana:");

  /*IEvent* damageEvent = new game::DamageTakenEvent(EVENT_ON_DAMAGE_TAKEN, game::onDamageTakenFire);
  EventManager::addEvent(damageEvent);
  IEvent* deathEvent = new game::DeathEvent(EVENT_ON_DEATH, game::onDeathFire);
  EventManager::addEvent(deathEvent);*/

  /*BasePlayer* player1 = new game::Player();
  PlayerResource::addPlayer(*player1);*/

  //Scene* mainScene = new game::MainScene();

  BasePlayer* player1 = new BasePlayer();
  PlayerResource::addPlayer(*player1);

  LOG << "loading first scene";

  Scene* scene = new Scene();
  Scene::loadFirstScene(*scene);

  
}
