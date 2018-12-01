#include "sprite_animation.h"
#include <core/texture.h>
#include <core/shader.h>
#include <core/resources.h>

using namespace oak;

SpriteAnimation::SpriteAnimation(
  std::string src,
  uint frameW,
  uint frameH,
  uint displayW,
  uint displayH,
  float frameTime,
  uint shaderID
)
{
  this->textureID = Resources::getTextureIDBySrc(src);
  this->shaderID = Resources::getShaderByID(shaderID).getID();
  this->frameW = frameW;
  this->frameH = frameH;
  this->displayH = displayH;
  this->displayW = displayW;
  this->frameTime = frameTime;
  this->shaderID = shaderID;
}

SpriteAnimation::~SpriteAnimation()
{

}

void SpriteAnimation::onDraw() const
{

}