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
    float frameDuration;
    float lastFrameTime;
    uint textureW;
    uint textureH;

    uint VAO;
    uint VBO;
    uint maxFramesX;
    uint maxFramesY;
    uint frameStartX;
    uint frameStartY;
    uint curFrameX;
    uint curFrameY;
    uint frameCount;
    uint curFrameCount;


    public:
      SpriteAnimation(
        std::string src,
        uint frameW,
        uint frameH,
        uint displayW,
        uint displayH,
        float frameDuration,
        std::string shaderName,
        uint frameCount,
        uint frameStartX,
        uint frameStartY
      );
      ~SpriteAnimation();

      void onUpdate() override;
      void onDraw() const override;
    private:
      void setFrame(uint frameX, uint frameY);
  };
}
#endif