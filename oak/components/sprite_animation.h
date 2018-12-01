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
    uint shaderID;
    uint frameW;
    uint frameH;
    uint displayW;
    uint displayH;
    float frameTime;
    uint textureW;
    uint textureH;


    public:
      SpriteAnimation(
        std::string src,
        uint frameW,
        uint frameH,
        uint displayW,
        uint displayH,
        float frameTime,
        uint shaderID
      );
      ~SpriteAnimation();


      void onDraw() const override;
  };
}
#endif