#include "main_scene.h"
#include <oak.h>
#include "../unit.h"
#include <core/player_resource.h>
#include "../prefabs/u_player.h"
#include "../player.h"
#include "../prefabs/camera_controller.h"
#include "../prefabs/u_dummy.h"
#include <debug.h>
#include <ui/ui.h>
#include "../ui/action_panel.h"
#include "../oak/components/rigid_body_2d.h"
#include "../prefabs/wall_test.h"

using namespace game;
using namespace oak;
using namespace oak::ui;


void MainScene::onLoad()
{
  Resources::addTexture("player.png");
  Resources::addTexture("wall.jpg");
  Resources::addTexture("face.png");
  Resources::addTexture("dummy.png");
  Resources::addTexture("anim_test2.png");
  Resources::addTexture("wolf_sheet.png");
  Resources::addTexture("action_panel.png");
  

  Camera::position = glm::vec3(0, 0, 0);

  Entity* ground = new Entity();
  Sprite* groundSprite = new Sprite("wall.jpg", 0, 0, 500, 500, 800.0f, 800.0f, "default");
  ground->addComponent(groundSprite);
  ground->instantiate();

  
  Player& player1 = static_cast<Player&>(PlayerResource::getPlayerByIndex(0));
  Unit* playerUnit = new prefab::UPlayer();
  playerUnit->instantiate();
  player1.setAssignedUnit(*playerUnit);


  prefab::CameraController* camController = new prefab::CameraController();
  camController->followTarget(playerUnit->getID());
  camController->instantiate();

  prefab::UDummy* dummy = new prefab::UDummy();
  dummy->instantiate(200.0f, 100.0f);

  prefab::UDummy* dummy2 = new prefab::UDummy();
  dummy2->instantiate(-200.0f, 80.0f);

  auto* comp = new game::ui::ActionPanel();
  comp->offset.x = 10.0f;
  UICanvas::addComponent(UI_COMPONENT_ACTION_PANEL, comp);

  auto* wall1 = new WallTest(50.0f, 200.0f);
  wall1->instantiate(100.0f, 0.0f);

  auto* wall3 = new WallTest(100.0f, 200.0f);
  wall3->instantiate(100.0f, 200.0f);

  float radius = 40.0f;
  Entity* wallTest2 = new Entity();
  wallTest2->addComponent(new Sprite("face.png", radius*2.0f, radius*2.0f));
  wallTest2->addCollision(new CollisionCircle(radius, 0.0f, 0.0f));
  wallTest2->addRigidBody(new RigidBody2D(true));
  wallTest2->instantiate(-100.0f, -20.0f);
}
