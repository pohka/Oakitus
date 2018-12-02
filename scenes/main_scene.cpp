#include "main_scene.h"
#include <oak.h>
#include "../unit.h"
#include <core/player_resource.h>
#include "../prefabs/u_player.h"
#include "../player.h"
#include "../prefabs/camera_controller.h"
#include "../prefabs/u_dummy.h"
#include <debug.h>

using namespace game;
using namespace oak;


void MainScene::onLoad()
{
  Resources::addTexture("player.png");
  Resources::addTexture("wall.jpg");
  Resources::addTexture("face.png");
  Resources::addTexture("dummy.png");
  Resources::addTexture("anim_test2.png");

  

  Camera::position = glm::vec3(0, 0, 0);

  Entity* ground = new Entity();
  Sprite* groundSprite = new Sprite("wall.jpg", 0, 0, 500, 500, 800.0f, 800.0f, "default");
  ground->addComponent(groundSprite);
  ground->instantiate();

  
  Player* player1 = static_cast<Player*>(PlayerResource::getPlayerByIndex(0));
  Unit* playerUnit = new prefab::UPlayer();
  playerUnit->instantiate();
  player1->setAssignedUnit(*playerUnit);


  prefab::CameraController* camController = new prefab::CameraController();
  camController->followTarget(playerUnit->getID());
  camController->instantiate();

  prefab::UDummy* dummy = new prefab::UDummy();
  dummy->instantiate(200.0f, 100.0f);
}
