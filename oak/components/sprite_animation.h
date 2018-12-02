#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <core/component.h>
#include <string>
#include <core/types.h>

namespace oak
{

  class SpriteAnimation
  {

    uint textureID;
    uint shaderID;
    uint frameW;
    uint frameH;
    uint displayW;
    uint displayH;
    float frameDuration;
    float lastFrameTime;
    uint textureW;
    uint textureH;

    uint VAO;
    uint VBO;
    uint maxFramesX;
    uint maxFramesY;
    uint startFrameY;
    uint curFrameX;
    uint curFrameY;
    uint totalFrameCount;
    uint curFrameCount;
    float totalAnimDuration;


    public:
      SpriteAnimation(
        std::string src,
        uint frameW,
        uint frameH,
        uint displayW,
        uint displayH,
        float frameDuration,
        std::string shaderName,
        uint totalFrameCount,
        uint startFrameY
      );
      ~SpriteAnimation();

      void reset();
      bool onUpdate();
      void onDraw(float positionX, float positionY) const;
      float getTotalAnimDuration() const;
    private:
      void setFrame();
  };
}
#endif