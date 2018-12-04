#include "fallback.h"
#include "core/resources.h"
#include "core/base_player.h"
#include "oak_def.h"

using namespace oak;

Shader Fallback::shader = Shader("default", false);
Texture Fallback::texture = Texture("fallback.png", false);
BasePlayer Fallback::basePlayer = BasePlayer();

Entity Fallback::entity = Entity(true);

SpriteAnimation Fallback::spriteAnim = SpriteAnimation(
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

Animator Fallback::animator = Animator(
  1,
  &spriteAnim,
  true
);


void Fallback::init()
{
  //set default resources
  shader.load();
  Resources::addShader(shader);

  texture.load();
  Resources::addTexture(texture);

  spriteAnim.load();
  animator.setAnim(1, true);
  entity.addComponent(&animator);
}

void Fallback::update()
{
  entity.onUpdate();
  animator.onUpdate();
}

void Fallback::draw()
{
  animator.onDraw();
}