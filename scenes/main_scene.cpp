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
#include "../ui/inventory_menu.h"

using namespace game;
using namespace oak;
using namespace ion;


void MainScene::onLoad()
{
  Resources::addTexture("player.png");
  Resources::addTexture("wall.jpg");
  Resources::addTexture("face.png");
  Resources::addTexture("dummy.png");
  Resources::addTexture("anim_test2.png");
  Resources::addTexture("wolf_sheet.png");
  Resources::addTexture("action_panel.png");
  Resources::addTexture("anim_arrow.png");
  Resources::addTexture("inventory_bg.png");

  //ui
  //testing style classes
  Style* testStyle = new Style("inv-item test");
  testStyle->set(STYLE_HEIGHT, 200.0f);
  UICanvas::addStyle(testStyle);
  LOG << "--------";
  LOG << "inv-item classList:";
  for (uint i = 0; i < testStyle->classList.size(); i++)
  {
    LOG << testStyle->classList[i];
  }
  LOG << "--------";


  auto* comp = new ActionPanel();
  //comp->offset.x = 10.0f;
  UICanvas::addComponent(UI_COMPONENT_ACTION_PANEL, comp);

  auto* inv = new InventoryMenu();
  UICanvas::addComponent(UI_COMPONENT_INVENTORY_MENU, inv);


  Camera::position = glm::vec3(0, 0, 0);

  Entity* ground = new Entity();
  Sprite* groundSprite = new Sprite("wall.jpg", 0, 0, 500, 500, 800.0f, 800.0f, "default");
  ground->addComponent(groundSprite);
  ground->create();

  
  Player& player1 = static_cast<Player&>(PlayerResource::getPlayerByIndex(0));
  Unit* playerUnit = new prefab::UPlayer();
  playerUnit->create();
  player1.setAssignedUnit(*playerUnit);
  

  prefab::UDummy* dummy = new prefab::UDummy();
  dummy->create(200.0f, 100.0f);

  //prefab::UDummy* dummy2 = new prefab::UDummy();
  //dummy2->instantiate(-250.0f, 100.0f);

  //prefab::UDummy* dummy3 = new prefab::UDummy();
  //dummy3->instantiate(-250.0f, 150.0f);

  //prefab::UDummy* dummy4 = new prefab::UDummy();
  //dummy4->instantiate(-200.0f, 80.0f);

  for (uint i = 0; i < 1; i++)
  {
    for (uint j = 0; j < 1; j++)
    {
      prefab::UDummy* dummy0 = new prefab::UDummy();
      dummy0->create(-200.0f + j * 50.0f, 80.0f + i * 50.0f);
    }
  }


  Entity* ball = new Entity();
  ball->addComponent(new Sprite("face.png", 60.0f, 60.0f));
  ball->addCollision(new CollisionCircle(30.0f, 0.0f, 00.0f));
  ball->addRigidBody(new RigidBody2D(false));
  ball->create(-100.0f, -200.0f);

  prefab::CameraController* camController = new prefab::CameraController();
  camController->followTarget(playerUnit->getID());
  camController->create();

 


  auto* wall1 = new WallTest(50.0f, 200.0f);
  wall1->create(100.0f, 0.0f);

  auto* wall3 = new WallTest(100.0f, 200.0f);
  wall3->create(100.0f, 200.0f);

  float radius = 40.0f;
  Entity* wallTest2 = new Entity();
  wallTest2->addComponent(new Sprite("face.png", radius*2.0f, radius*2.0f));
  wallTest2->addCollision(new CollisionCircle(radius, 0.0f, 0.0f));
  wallTest2->addRigidBody(new RigidBody2D(true));
  wallTest2->create(-100.0f, -20.0f);
}
