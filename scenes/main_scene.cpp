#include "main_scene.h"
#include <oak.h>
#include "../unit.h"
#include <core/player_resource.h>
#include "../prefabs/u_player.h"
#include "../player.h";

using namespace game;
using namespace oak;


void MainScene::onLoad()
{
  Resources::addTexture("player.png");
  Resources::addTexture("wall.jpg");

  Shader* shader = Resources::findShaderByName("default");
  uint shaderID = shader->getID();

  Camera::position = glm::vec3(0, 0, 0);

  Entity* ground = new Entity();
  Sprite* groundSprite = new Sprite("wall.jpg", 0, 0, 500, 500, 800.0f, 800.0f, shaderID);
  ground->addComponent(*groundSprite);
  ground->instantiate();

  Player* player1 = new Player();
  PlayerResource::addPlayer(*player1);
  //Player* player1 = PlayerResource::getPlayerByIndex(0);
  Unit* playerUnit = new UPlayer();
  playerUnit->instantiate();
  player1->setAssignedUnit(*playerUnit);
  
}
