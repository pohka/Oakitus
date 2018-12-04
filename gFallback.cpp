#include "gFallback.h"
#include "oak/fallback.h"
#include "game_def.h"

using namespace game;

Player gFallback::player = Player();

Unit gFallback::unit = Unit();

oak::Entity gFallback::entity = oak::Entity(true);

oak::SpriteAnimation gFallback::spriteAnim = oak::SpriteAnimation(
  "fallback.png",
  0,
  8, 8, 32, 32,
  1.0f,
  "default",
  1,
  0,
  true,
  false
);

oak::Animator gFallback::animator = oak::Animator(
  1,
  &spriteAnim,
  true
);



void gFallback::init()
{
  spriteAnim.load();
  entity.addComponent(&animator);
}