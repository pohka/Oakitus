#include "demo_scene.h"
#include <oak/oak.h>
#include "../movement_cmd.h"
#include <oak/debug.h>

using namespace sample;
using namespace oak;

//template <typename T>
//void findComp(Entity* ent, std::vector<T*>& out)
//{
//   for (uchar i = 0; i < TICK_GROUP_MAX; i++)
// {
////   for (Component* comp : ent->componentGroups[i])
////   {
////    // casted = ;
////     if (dynamic_cast<const T*>(comp) != nullptr)
////     {
//////       out.push_back(comp);
////     }
////   }
// }
//}


void DemoScene::onLoad()
{
  Resources::addTexture("face.png");
  Resources::addTexture("anim_test2.png");
  Entity* ent = new Entity();
  ent->addComponent(new Sprite("face.png", 60.0f, 60.0f));
  Animator* animator = new Animator(
    1,
    new SpriteAnimation(
      "anim_test2.png",
      0,
      192, 192,
      100, 100,
      0.04f,
      "default",
      14,
      0,
      true
    )
  );
  ent->addComponent(animator);
  ent->create(0.0f, 0.0f);


  Actor* unit = new Actor();
  unit->addComponent(new Sprite("face.png", 30.0f, 30.0f));
  unit->position.x = 100.0f;
  unit->create();
  Player* player = PlayerResource::getLocalPlayer();
  player->assignActor(unit);

  Command* movement = new MovementCMD();
  player->addCommand(movement);
  
  std::vector<Sprite*> ss;
  ent->getComponents<Sprite>(ss);
  LOG << "SS:" << ss.size();

  Sprite* s = ent->getComponent<Sprite>();
  if (s != nullptr)
  {
    LOG << "FOUND:" << s->isTickable() << ":" << s->getTickingInterval();
  }


}