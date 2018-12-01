#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <core/component.h>
#include <string>
#include <core/types.h>

namespace oak
{
  class SpriteAnimation : public Component
  {
    uint textureID;
    uint frameWidth;
    uint frameHeight;


    public:
      SpriteAnimation(std::string src, uint frameWidth, uint frameHeight, uint shaderID);
      ~SpriteAnimation();

      void onDraw() const override;
  };
}
#endif