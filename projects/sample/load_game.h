#include <oak/oak_setup.h>
//#include <oak/core/player_resource.h>
//#include <oak/ui/ui.h>
#include <oak/debug.h>
#include <oak/oak.h>

void oak::Oakitus::load()
{
  BasePlayer* player1 = new BasePlayer();
  PlayerResource::addPlayer(*player1);

  Scene* scene = new Scene();
  Scene::loadFirstScene(*scene);

  Resources::rootPath = "../projects/"+ MetaLoader::getConfigVal("project") + "/resources/";
  Resources::addTexture("face.png");
  Entity* ent = new Entity();
  ent->addComponent(new Sprite("face.png", 60.0f, 60.0f));
  ent->create(0.0f, 0.0f);
}
