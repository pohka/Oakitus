#include "ai_test.h"
#include <oak.h>

using namespace game;
using namespace oak;

AITest::AITest()
{

}

void AITest::onUpdate()
{
  Entity* playerUnit = Entity::findEntityByName("u_player");
  if (playerUnit != nullptr)
  {
    glm::vec3 dir = glm::normalize(playerUnit->position - entity->position);
    float speed = 50.0f;
    entity->position += dir * speed * Time::deltaTime();
  }
}