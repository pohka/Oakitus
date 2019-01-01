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

    uint VAO;
    uint VBO;
    uint maxFramesX;
    uint maxFramesY;
    uint startFrameY;
    uint curFrameX;
    uint curFrameY;
    uint totalFrameCount;
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
        uint shaderID,
        uint totalFrameCount,
        uint startFrameY,
        bool isLooping
      );
      ~SpriteAnimation();

      void load();
      void reset();
      //bool onTick(uchar direction, bool hasChangedDirection);
      void onRender(float positionX, float positionY) const;
      uchar getPriority() const;
      Animator* animator;
      float getFrameDuration() const;
      uint getFrameCount() const;
      bool getIsLooping() const;
      void setFrame(uint frameIndex, uchar direction);

    private:
      
      void setVertexAttrs() const;
  };
}
#endif