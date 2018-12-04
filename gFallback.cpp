#include "gFallback.h"
#include "oak/fallback.h"
#include "game_def.h"

using namespace game;

Player gFallback::player = Player();

Unit gFallback::unit = Unit();

oak::SpriteAnimation gFallback::spriteAnim = oak::SpriteAnimation(
  "fallback.png",
  ANIM_PRIORITY_LOWEST,
  8, 8, 32, 32,
  1.0f,
  "default",
  1,
  0,
  true,
  false
);

oak::Animator gFallback::animator = oak::Animator(
  ANIM_TYPE_IDLE,
  &spriteAnim,
  true
);



void gFallback::init()
{
 // player.setAssignedUnit(unit);
  spriteAnim.load();
  //unit.addAnimator(&animator);
}