#include "sample_scene.h"
#include "move_script.h"
#include "oak/core/store.h"
#include "player.h"

using namespace oak;
using namespace game;

SampleScene::SampleScene() {}

SampleScene::~SampleScene() {}

void SampleScene::onLoad()
{
  Resources::addTexture("wall.jpg");
  Resources::addTexture("face.png");
  Shader* shader = Resources::findShaderByName("default");
  uint shaderID = shader->getID();

  Entity* gPlayer = Store::findEntityByName("player");
  if (gPlayer == nullptr)
  {
    Entity* player = new Player();
    player->isGlobal = true;
    Store::addEntity(*player);
  }
  else
  {
    std::cout << "found global player" << std::endl;
    gPlayer->position = glm::vec3(1.0f, 0.0f, 0.0f);
  }

  Entity* ground = new Entity();
  //ground->position.x = 1.0f;
  Sprite* groundSprite = new Sprite("wall.jpg", 0, 0, 500, 500, 800.0f, 800.0f, shaderID);
  ground->addComponent(*groundSprite);
  ground->layerID = -1;
  Store::addEntity(*ground);
}