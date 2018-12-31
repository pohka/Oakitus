#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <oak/core/component.h>
#include <string>
#include <oak/core/types.h>



namespace oak
{
  class Animator;

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
        bool isLooping,
        bool isOnHeap = true
      );
      ~SpriteAnimation();

      void load();
      void reset();
      bool onTick(uchar direction, bool hasChangedDirection);
      void onRender(float positionX, float positionY) const;
      float getTotalAnimDuration() const;
      uchar getPriority() const;
      Animator* animator;

    private:
      void setFrame(uchar direction);
      void setVertexAttrs() const;
  };
}
#endif