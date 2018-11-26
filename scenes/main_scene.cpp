#include "main_scene.h"
#include <oak.h>
#include "../unit.h";
#include "../player_resource.h"

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

  Player* player1 = PlayerResource::getPlayerByIndex(0);
  Unit* playerUnit = new Unit();
  Sprite* playerSprite = new Sprite("player.png", 0, 0, 32, 40, 32.0f, 40.0f, shaderID);
  playerUnit->addComponent(*playerSprite);
  playerUnit->setOwner(*player1);
  playerUnit->instantiate();
}
