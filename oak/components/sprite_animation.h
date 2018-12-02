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
    bool isLooping;
    uchar priority;

    public:
      SpriteAnimation(
        std::string src,
        uchar priority,
        uint frameW,
        uint frameH,
        uint displayW,
        uint displayH,
        float frameDuration,
        std::string shaderName,
        uint totalFrameCount,
        uint startFrameY,
        bool isLooping
      );
      ~SpriteAnimation();

      void reset();
      bool onUpdate(uchar direction, bool hasChangedDirection);
      void onDraw(float positionX, float positionY) const;
      float getTotalAnimDuration() const;
      uchar getPriority() const;

    private:
      void setFrame(uchar direction);
  };
}
#endif