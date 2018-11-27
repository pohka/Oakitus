#include "arrow.h"
#include <oak.h>
#include "../scripts/linear_projectile.h"

using namespace game::prefab;
using namespace oak;

Arrow::Arrow()
{
  Sprite* sprite = new Sprite("face.png", 16.0f, 16.0f);
  addComponent(*sprite);


  LinearProjectile* proj = new LinearProjectile(
    Camera::cursorToWorld2D(),
    1000.0f,
    1000.0f,
    true
  );
  addScript(*proj);
}

Arrow::~Arrow()
{

}