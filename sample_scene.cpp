#include "sample_scene.h"
#include "move_script.h"
#include "oak/core/store.h"
#include "player.h"
#include "world.h"
#include "map_loader.h"
#include "oak/core/debug.h"

using namespace oak;
using namespace game;

SampleScene::SampleScene() {}

SampleScene::~SampleScene() {}

void SampleScene::onLoad()
{
  Store::camera->position = glm::vec3(0, 0, 0);

  Resources::addTexture("wall.jpg");
  Resources::addTexture("face.png");
  Resources::addTexture("player.png");
  Resources::addTexture("tilesets/cave.png");
  Resources::addTexture("tilesets/test.png");
  Shader* shader = Resources::findShaderByName("default");
  uint shaderID = shader->getID();

  World* world = MapLoader::loadMap("map2.xml");
  Store::addEntity(*world);
  world->layerID = -1;


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
  //Store::addEntity(*ground);

  LOG << "test debuging " << 123;
}