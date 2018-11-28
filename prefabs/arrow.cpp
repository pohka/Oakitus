#include "arrow.h"
#include <oak.h>
#include "../scripts/linear_projectile.h"

using namespace game::prefab;
using namespace oak;

Arrow::Arrow(glm::vec2 targetPos)
{
  Sprite* sprite = new Sprite("face.png", 16.0f, 16.0f);
  addComponent(*sprite);


  LinearProjectile* proj = new LinearProjectile(
    targetPos,
    1000.0f,
    1000.0f,
    true
  );
  addScript(*proj);
}

Arrow::~Arrow()
{

}