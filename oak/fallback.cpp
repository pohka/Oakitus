#include "fallback.h"
#include "core/resources.h"
#include "core/base_player.h"

using namespace oak;

Shader Fallback::shader = Shader("default", false);
Texture Fallback::texture = Texture("fallback.png", false);
BasePlayer Fallback::basePlayer = BasePlayer();


void Fallback::init()
{
  //set default resources
  shader.load();
  Resources::addShader(shader);

  texture.load();
  Resources::addTexture(texture);
}