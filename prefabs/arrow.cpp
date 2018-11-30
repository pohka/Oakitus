#include "arrow.h"
#include <oak.h>
#include "../scripts/linear_projectile.h"
#include "../ability.h"

using namespace game::prefab;
using namespace oak;

Arrow::Arrow(glm::vec2 targetPos, game::Faction casterFaction)
{
  Sprite* sprite = new Sprite("face.png", 16.0f, 16.0f);
  addComponent(sprite);
  addCollision(new CollisionCircle(16.0f, 0.0f, 0.0f));

  LinearProjectile* proj = new LinearProjectile(
    targetPos,
    150.0f,
    1000.0f,
    true,
    TargetTeam::FRIENDLY_TEAM,
    casterFaction
  );
  addComponent(proj);
  collisionLayer = CollisionLayer::PROJECTILE;
}

Arrow::~Arrow()
{
  
}