#include "arrow.h"
#include <oak.h>
#include "../scripts/linear_projectile.h"
#include "../ability.h"
#include <debug.h>


using namespace game::prefab;
using namespace oak;
using namespace game;

Arrow::Arrow(glm::vec2 targetPos, Unit& caster, uint abilityID)
{
  Sprite* sprite = new Sprite("face.png", 16.0f, 16.0f);
  addComponent(sprite);
  addCollision(new CollisionCircle(16.0f, 0.0f, 0.0f));

  LinearProjectile* proj = new LinearProjectile(
    targetPos,
    20,
    150.0f,
    1000.0f,
    true,
    TARGET_TEAM_BOTH,
    caster.getFaction(),
    abilityID,
    caster.getID()
  );
  addComponent(proj);
  collisionLayer = CollisionLayer::PROJECTILE;
}

Arrow::~Arrow()
{
  LOG << "here";
}