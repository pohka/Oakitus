#include "arrow.h"
#include <oak.h>
#include "../scripts/linear_projectile.h"

using namespace game;
using namespace oak;

Arrow::Arrow()
{
  Sprite* sprite = new Sprite("face.png", 0, 0, 1000, 1000, 16.0f, 16.0f, NULL);
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